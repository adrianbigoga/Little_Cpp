cmake_minimum_required(VERSION 3.30)
project(training)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_DEBUG_TYPE debug)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
