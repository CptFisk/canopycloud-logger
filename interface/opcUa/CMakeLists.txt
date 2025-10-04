cmake_minimum_required(VERSION 2.8.12...3.21)
project(OpcUa)


# Detect platform
if(WIN32 AND MINGW)
    # MSYS2/MinGW-specific OpenSSL setup
    set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
    set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
    set(OPENSSL_LIBRARIES "${OPENSSL_ROOT_DIR}/lib/libssl.dll.a;${OPENSSL_ROOT_DIR}/lib/libcrypto.dll.a")
endif()
#Find package
find_package(OpenSSL REQUIRED)


include(FetchContent)

FetchContent_Declare(open62541
        URL https://github.com/open62541/open62541/archive/refs/tags/v1.4.13.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Declare(nlohmann
        URL https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)


FetchContent_MakeAvailable(open62541 nlohmann)

set(CMAKE_CXX_STANDARD 23)

MESSAGE(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
        ${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/opc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/security.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cert.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/utility/byteStringLoad.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utility/byteStringClone.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utility/nodes.cpp


)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
        ${PROJECT_NAME}
        open62541
        nlohmann_json::nlohmann_json
        Interface

        OpenSSL::SSL
        OpenSSL::Crypto
)
