cmake_minimum_required(VERSION 2.8.12...3.21)
project(canopycloud_logger)

include(ExternalProject)
include(FetchContent)

FetchContent_Declare(nlohmann
        URL https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)


FetchContent_MakeAvailable(nlohmann)
#Interfaces
add_subdirectory(interface/base)
add_subdirectory(interface/opcUa)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        ${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/src/loader.cpp
        main.cpp
)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/interface
)

target_link_libraries(
        ${PROJECT_NAME}
        Interface
        OpcUa
        nlohmann_json::nlohmann_json
)

file(COPY ${CMAKE_SOURCE_DIR}/config DESTINATION ${CMAKE_CURRENT_BINARY_DIR})