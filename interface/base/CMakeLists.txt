cmake_minimum_required(VERSION 2.8.12...3.21)
project(Interface)

set(CMAKE_CXX_STANDARD 20)

MESSAGE(STATUS ${CMAKE_CURRENT_SOURCE_DIR})


add_library(
        ${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/base.cpp
)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
