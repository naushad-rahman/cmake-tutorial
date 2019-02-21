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


# path to find own modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# # # # # # # # # # # # # # # # # # # # # #
# CMake Options
# # # # # # # # # # # # # # # # # # # # # #

option( DEVELOPER "Compile with extra warnings" OFF )
option( ALLWARNINGS "Compile with even more warnings" OFF )

set(CLANG_SANITIZER "none" CACHE STRING "Compile with the respective sanitizer")
set_property(CACHE CLANG_SANITIZER PROPERTY STRINGS none address memory thread)


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

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/doxygen-conf/doxygen.conf.in)
    set(DOXYGEN_OUT ${PROJECT_SOURCE_DIR}/docs/output/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Maths
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
endif()