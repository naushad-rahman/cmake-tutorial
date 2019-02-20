cmake_minimum_required(VERSION 3.10)
project(dvSim-Maths CXX)

set(DVSIMMATH_MAJOR_VERSION 0)
set(DVSIMMATH_MINOR_VERSION 1)
set(DVSIMMATH_PATCH_VERSION 0)
set(DVSIMMATH_IS_RELEASE 1)

set(DVSIMMATH_VERSION ${DVSIMMATH_MAJOR_VERSION}.${DVSIMMATH_MINOR_VERSION}.${DVSIMMATH_PATCH_VERSION})
if(NOT DVSIMMATH_IS_RELEASE)
  set(DVSIMMATH_VERSION "${DVSIMMATH_VERSION}+")
endif()
set(DVSIMMATH_VERSION "${DVSIMMATH_VERSION}")
set(PACKAGE_NAME "CasADi")
set(PACKAGE_VERSION ${DVSIMMATH_VERSION})
set(PACKAGE_SO_VERSION "3.5")
set(PACKAGE_DESCRIPTION "CasADi is a symbolic framework for automatic differentation and numeric optimization")
set(PACKAGE_AUTHOR "Naushad Rahman & Sreeraj ")
set(PACKAGE_MAINTAINER "Dvsim Backedn Team")


message("CMAKE_CXX_COMPILER    = ${CMAKE_CXX_COMPILER}")
message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_COMPILER_IS_GNUCXX  =${CMAKE_COMPILER_IS_GNUCXX}")



# path to find own modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

##########################################
# CLANG TIDY 
##########################################

option(WITH_CLANG_TIDY "Compile with support for clang-tidy" OFF)
if (WITH_CLANG_TIDY)
include(clang-tidy REQUIRED)
message("WITH_CLANG_TIDY_NEW = ${WITH_CLANG_TIDY_NEW}")
endif()


################################################################################
############################### compiler warnings ##############################
################################################################################
include(compiler-options REQUIRED)
#######################################################################
############################# -fPIC ###################################
#######################################################################
# the following commands are needed to fix a problem with the libraries
# for linux 64 bits
if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
  message(STATUS "x86_64 architecture detected - setting flag -fPIC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fPIC")
endif()


# Monolithic version
add_subdirectory(Maths)

enable_testing()
OPTION(BUILD_TESTS "dvMath test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()


add_subdirectory(misc)

#####################################################
######################### docs ######################
#####################################################
option(WITH_DOC "Enable documentation generation" OFF)
if(WITH_DOC)
  set(DOXYFILE_LATEX "NO")
  set(DOXYFILE_IN_DIR ${PROJECT_SOURCE_DIR}/docs/api)
  set(DOXYFILE_OUTPUT_DIR  ${PROJECT_SOURCE_DIR}/docs/api)
  set(DOXYFILE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/Maths)
  include(UseDoxygen OPTIONAL)
  add_custom_target(tutor)
endif()