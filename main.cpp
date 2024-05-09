#include "LLK/LLKLicense.h"

#include "nlohmann/json.hpp"

#include <iostream>
#include <fstream>

const char* LLKFeatureLicenseTypeDescription(LLKFeatureLicenseType type) {
	switch (type) {
		case LLKFeatureLicenseType::LLK_PERPETUAL:         return "Perpetual, unlimited licensing model";
		case LLKFeatureLicenseType::LLK_FIXED_TIME_PERIOD: return "Trial(Time Period) licensing model";
		case LLKFeatureLicenseType::LLK_EXACT_DATE:        return "Based on the duration for which the product is used";
		case LLKFeatureLicenseType::LLK_EXECUTIONS:        return "Based on the number of times the product is used within the specified period";
		default: return "Unknown";
	}
}


int main() {
	using json = nlohmann::json;
	std::ifstream fin("./data/license.json");
	if (!fin.is_open()) {
		std::cerr << "Failed to open `./data/license.json`" << std::endl;
		return -1;
	}

	const json& licenseConf = json::parse(fin);
	if (licenseConf.empty()) {
		return -1;
	}

	uint32_t llkVersionMajor = 0;
	uint32_t llkVersionMinor = 0;
	uint32_t llkVersionRelease  = 0;
	const LLKStatus getVersionStatus = llkGetVersion(&llkVersionMajor, &llkVersionMinor, &llkVersionRelease);
	std::cout << "API Version: " << llkVersionMajor << "." << llkVersionMinor << "." << llkVersionRelease << std::endl;
	
	const std::string& vendorID = licenseConf["Licensing"]["VendorID"];
	const std::string& serialNumber = licenseConf["Licensing"]["SerialNumber"];
	const std::string& pathToSaveTheLicenseData = licenseConf["Licensing"]["FilePath"];
	const std::string& server = licenseConf["Licensing"]["Server"];

	const json& inputJSON =
		{
			{ "VendorID", vendorID },
			{ "SerialNumber" , serialNumber },
			{ "PathToSaveTheLicenseData" , pathToSaveTheLicenseData },
			{ "HostName" , server },
		};

	const LLKStatus activateLicenseStatus = llkActivateLicense(inputJSON.dump().c_str());
	std::cout << "llkActivateLicense - ErrorCode: " << llkStatusDescription(activateLicenseStatus) << std::endl;
	if (activateLicenseStatus != LLKStatus::LLK_OK)  {
		std::cerr << llkStatusDescription(activateLicenseStatus) << std::endl;
		return -1;
	}

	json jsonLicenseInfo;

{
	char* rawLicenseInfo = nullptr;
	const LLKStatus licenseInfoStatus = llkGetLicenseInfo(&rawLicenseInfo);

	jsonLicenseInfo = json::parse(rawLicenseInfo);
	std::cout << jsonLicenseInfo.dump(1) << std::endl;

	/*nullptr is ok for llkFree*/
	llkFree(rawLicenseInfo);
}

	const json& featuresList = jsonLicenseInfo["Features"];
	for (const auto& feature : featuresList) {
		const uint32_t featureID = feature["ID"].get<uint32_t>();
		const LLKStatus errorCode = llkFeatureCheck(featureID);
		std::cout << "llkFeatureCheck feature ID: " << featureID << ", ErrorCode: " << llkStatusDescription(errorCode) << std::endl;

		LLKFeatureLicenseType type = LLKFeatureLicenseType::LLK_UNKNOWN;
		const LLKStatus getFeatureLicensingTypeStatus = llkGetFeatureLicensingType(featureID, &type);
		std::cout << "FeatureLicenseType: " << LLKFeatureLicenseTypeDescription(type) << std::endl;
	}

{
	const uint32_t nonExistentFeatureID = 9823144;
	const LLKStatus errorCode = llkFeatureCheck(nonExistentFeatureID);
	std::cout << "llkFeatureCheck feature ID: " << nonExistentFeatureID << ", ErrorCode: " << llkStatusDescription(errorCode) << std::endl;
}

{
	char* featureInfoJson = nullptr;
	const uint32_t featureId = 0;
	const LLKStatus llkGetFeatureInfoStatus = llkGetFeatureInfo(featureId, &featureInfoJson);
	if (llkGetFeatureInfoStatus == LLKStatus::LLK_OK) {
		std::cout << json::parse(featureInfoJson).dump(1) << std::endl;
	}

	/*nullptr is ok for llkFree*/
	llkFree(featureInfoJson);
}

	return 0;
}
