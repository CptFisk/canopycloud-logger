cmake_minimum_required(VERSION 2.8.12...3.21)
project(canopycloud_logger)

include(ExternalProject)

#Interfaces
add_subdirectory(interface/base)
add_subdirectory(interface/opcUa)

set(CMAKE_CXX_STANDARD 20)

add_executable(canopycloud_logger main.cpp)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
        ${PROJECT_NAME}
        Interface
        OpcUa

        open62541
)
