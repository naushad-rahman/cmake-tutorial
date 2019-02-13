cmake_minimum_required(VERSION 3.0)
project(dvSim-Projects)

enable_testing()

# Monolithic version
add_subdirectory(Maths)

OPTION(BUILD_TESTS "dvMath test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()