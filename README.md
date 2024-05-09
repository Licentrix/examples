# LightLicensingKit examples

The `Complete API documentation` is available at [https://doc.masur.pw/](https://doc.masur.pw/docs/LicensingAPI)

## How to Build and Launch on Linux

```sh
cd '<llk root dir>'

export INSTALL_PATH="<give some install path>"

# Choose one of the types
export BUILD_TYPE="RELEASE|RELWITHDEBINFO"

export CMAKE_DEFAULTS="
    -DLLK_ROOT_DIR='<full path to llk root dir>' \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH} \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DNLOHMAN_JSON_ROOT='<nlohmann json root>"

mkdir build-examples-${BUILD_TYPE}
cd build-examples-${BUILD_TYPE}

cmake ../examples $(eval echo ${CMAKE_DEFAULTS})
cmake --build . --config $BUILD_TYPE --target install

mkdir data
cp license.json data/license.json
$ ./example
```

## How to Build and Launch on Windows

```sh
cd '<llk root dir>'

SET INSTALL_PATH="<give some install path>"

mkdir build-examples
cd build-examples

cmake ../examples ^
    -DLLK_ROOT_DIR='<full path to llk root dir>' ^
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PATH} ^
    -DNLOHMAN_JSON_ROOT='<nlohmann json root>

cmake --build . --target install

mkdir data
cp license.json data/license.json
./example.exe
```

> [!NOTE]
> In this example we store the `license.json` and the `program key (license.l2c)` in the `data/` directory, but is not a prerequisite


### An example of `license.json`

```JSON
{
  "HostName": "masur.pw",
  "PathToSaveTheLicenseData": "./data/license.l2c",
  "SerialNumber": "989e79-140a9f1aw880-323b973g960d",
  "VendorID": "15cva7cyd4q0-a1f8t5d056b5"
}
```

| Field                    | Description                                                                                                                                                |
| :----------------------- |:---------------------------------------------------------------------------------------------------------------------------------------------------------- |
| HostName                 | License activation server address. The default value is masur.pw, **replace only with backup server, and only in case the primary server is unresponsive** |
| PathToSaveTheLicenseData | Local path to save the software program key (`license.l2c`)                                                                                                |
| SerialNumber             | The serial number is displayed on the [Licenses](https://dev.masur.pw/orders) page                                                                         |
| VendorID                 | Located at the top of the [Licenses](https://dev.masur.pw/orders) page                                                                                     |

### An example of output

```sh
API Version: 1.0.0
llkActivateLicense - ErrorCode: The operation status is successful
{
 "ActivationTimestamp": 1700034857,
 "ConnectedProducts": [
  {
   "Name": "Prod_0_v.1.0"
  }
 ],
 "Features": [
  {
   "ID": 1,
   "Name": "Test_1",
   "executionsLimit": 0,
   "licenseType": 2,
   "validFromDate": 1700034857,
   "validUpToDate": 1701993600
  },
  {
   "ID": 2,
   "Name": "Test_2",
   "executionsLimit": 0,
   "licenseType": 2,
   "validFromDate": 1700034857,
   "validUpToDate": 1701993600
  },
  {
   "ID": 0,
   "Name": "Test_0",
   "executionsLimit": 0,
   "licenseType": 2,
   "validFromDate": 1700034857,
   "validUpToDate": 1701993600
  }
 ],
 "SerialNumber": "989e79-140a9f1aw880-323b973g960d"
}
llkFeatureCheck feature ID: 1, ErrorCode: The operation status is successful
FeatureLicenseType: Based on the duration for which the product is used
llkFeatureCheck feature ID: 2, ErrorCode: The operation status is successful
FeatureLicenseType: Based on the duration for which the product is used
llkFeatureCheck feature ID: 0, ErrorCode: The operation status is successful
FeatureLicenseType: Based on the duration for which the product is used
llkFeatureCheck feature ID: 9823144, ErrorCode: The Feature not found
```

> [!NOTE]
> In this example we are using [nlohmann json](https://github.com/nlohmann/json), for parsing and pretty visualization of some inputs and outputs.
