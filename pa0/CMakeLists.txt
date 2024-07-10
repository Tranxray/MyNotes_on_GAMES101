cmake_minimum_required (VERSION 2.8.11)
project (Transformation)

find_package(eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(/usr/local/include)
message(STATUS "Eigen include directory: ${EIGEN3_INCLUDE_DIR}")

add_executable (Transformation main.cpp)
