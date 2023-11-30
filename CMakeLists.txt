cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(PROJECT_NAME "example")
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 20)

if (NOT EXISTS ${LLK_ROOT_DIR})
	message(FATAL_ERROR "LLK_ROOT_DIR not found!")
else()
	if(WIN32)
		set(SWAP_VAR "")
		string(REPLACE "\\" "/" SWAP_VAR ${LLK_ROOT_DIR})
		set(LLK_ROOT_DIR ${SWAP_VAR})
	endif()

	set(CMAKE_MODULE_PATH ${LLK_ROOT_DIR}/cmake/)
endif()

find_package(LLK REQUIRED)

if(LLK_FOUND)
	message(STATUS "[DEBUG] LLK_INCLUDE_DIRS: ${LLK_INCLUDE_DIRS}")
	message(STATUS "[DEBUG] LLK_LIBRARIES: ${LLK_LIBRARIES}")
	message(STATUS "[DEBUG] LLK_RUNTIME_LIBRARIES: ${LLK_RUNTIME_LIBRARIES}")
else()
	message(FATAL "LLK NOT_FOUND")
endif()

# nlohman_json
if (NOT EXISTS ${NLOHMAN_JSON_ROOT})
	message(FATAL_ERROR "nlohman_json not found!")
else()
	include_directories("${NLOHMAN_JSON_ROOT}/include")
endif()

set(SOURCES ${LLK_ROOT_DIR}/examples/main.cpp)

if(NOT WIN32)
	find_package(Threads REQUIRED)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${LLK_INCLUDE_DIRS})

if (LLK_USE_STATIC_LIBS)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${LLK_LIBRARIES})
else()
	target_link_libraries(${PROJECT_NAME} PRIVATE ${LLK_RUNTIME_LIBRARIES})
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
