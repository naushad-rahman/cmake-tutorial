cmake_minimum_required(VERSION 3.0)
project(dvSim-Projects)

enable_testing()

option(WITH_CLANG_TIDY "Compile with support for clang-tidy" OFF)
if(WITH_CLANG_TIDY)
#   include(ClangTidy REQUIRED)
  include(cmake/ClangTidy.cmake)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  if(WITH_EXTRA_WARNINGS)
    # -Wall leaks into clang-tidy (through compile_commands.json)
    # silently overruling the 'Checks' field.
    # These warnings come from external_packages
    set(EXTRA_CASADI_CXX_FLAGS "${EXTRA_CASADI_CXX_FLAGS} -Wno-overloaded-virtual -Wno-deprecated-register")
  endif()
endif()

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





add_subdirectory(misc)