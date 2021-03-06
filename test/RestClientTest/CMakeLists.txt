# CMake Version
CMAKE_MINIMUM_REQUIRED (VERSION 3.5.1)

# Project Name
PROJECT(RestClientTest)

# Configuration
SET(LUNA_SW_PLATFORM ${CMAKE_CURRENT_SOURCE_DIR}/../../)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(
	./ 
	${LUNA_SW_PLATFORM}/src/Library/ccCore/include
	${LUNA_SW_PLATFORM}/src/Library/ccNetwork/include
	${LUNA_SW_PLATFORM}/src/FossLibrary/ccJsonParser/include
	${LUNA_SW_PLATFORM}/src/FossLibrary/ccRestClient/include
)

link_directories(
	${LUNA_SW_PLATFORM}/build/lib
)

add_executable (RestClientTest
    src/main.cpp
)

TARGET_LINK_LIBRARIES(RestClientTest
 	ccRestClient
	ccJsonParser
	ccNetwork
	ccCore
    curl
    mbedtls
    mbedcrypto
    mbedx509	
	pthread
) 
