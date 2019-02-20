
# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.10) # GENERATOR_IS_MULTI_CONFIG

project(dvSim-Math VERSION 1.2.3)


if(MSVC)
  set(pdb_output_dir "${CMAKE_CURRENT_BINARY_DIR}/pdb-files")

  set( "${pdb_output_dir}")
  set(CMAKE_COMPILE_PDB_OUTCMAKE_PDB_OUTPUT_DIRECTORYPUT_DIRECTORY "${pdb_output_dir}")

  get_cmake_property(is_multi GENERATOR_IS_MULTI_CONFIG)
  if(is_multi)
    set(config_suffix "$<CONFIG>")
  else()
    set(config_suffix "")
  endif()

  # Introduce variables:
  # * CMAKE_INSTALL_LIBDIR
  # * CMAKE_INSTALL_BINDIR
  include(GNUInstallDirs)

  if(BUILD_SHARED_LIBS)
    set(pdb_dst ${CMAKE_INSTALL_BINDIR})
  else()
    set(pdb_dst ${CMAKE_INSTALL_LIBDIR})
  endif()

  install(
      DIRECTORY "${pdb_output_dir}/${config_suffix}/"
      DESTINATION ${pdb_dst}
  )
endif()


################################
# Adding Include File Path 
################################
file (GLOB HEADER_ALL "include/*.hpp")
file (GLOB HEADER_DATATYPESDEF "include/dataTypesdef/*.hpp")


################################
# Source Path 
################################
set( SOURCE 
    ${HEADER_ALL}
    ${HEADER_DATATYPESDEF}
    src/Complex.cpp
   )
# Create targets
add_library(dvsimMath SHARED ${SOURCE})


# Properties of targets
target_compile_definitions(dvsimMath PUBLIC "DVSIM_MATH_DEBUG=$<CONFIG:Debug>")


# Generate:
set(generated_headers "${CMAKE_CURRENT_BINARY_DIR}/generated_headers")
set(dvSimMath_export "${generated_headers}/dvsimMath/DVSIM_MATH_EXPORT.h")

include(GenerateExportHeader)
generate_export_header(dvsimMath EXPORT_FILE_NAME ${dvSimMath_export})


# Global includes. Used by all targets
target_include_directories(
    dvsimMath PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
    "$<BUILD_INTERFACE:${generated_headers}>"
)

# Link required library
# target_link_libraries(bar PUBLIC baz)


include(GNUInstallDirs)

################################
# Installing Path 
################################
# Layout. This works for all platforms:
#   * <prefix>/lib*/cmake/<PROJECT-NAME>
#   * <prefix>/lib*/
#   * <prefix>/include/
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)


message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
    "../cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/libbar.a
#   * <prefix>/lib/libbaz.a
#   * header location after install: <prefix>/include/foo/Bar.hpp
#   * headers can be included by C++ code `#include <foo/Bar.hpp>`
install(
    TARGETS dvsimMath
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Headers:
#   * Source/foo/Bar.hpp -> <prefix>/include/foo/Bar.hpp
#   * Source/foo/Baz.hpp -> <prefix>/include/foo/Baz.hpp
# install(
#     DIRECTORY "Source/foo"
#     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
#     FILES_MATCHING PATTERN "*.hpp"
# )

install (
    FILES ${HEADER_ALL} 
    DESTINATION  "${CMAKE_INSTALL_INCLUDEDIR}/dvsimMath"
)
install (
    FILES ${HEADER_DATATYPESDEF} 
    DESTINATION  "${CMAKE_INSTALL_INCLUDEDIR}/dvsimMath/dataTypesdef"
)

# Export headers:
#   * ${CMAKE_CURRENT_BINARY_DIR}/.../BAR_EXPORT.h -> <prefix>/include/foo/BAR_EXPORT.h
#   * ${CMAKE_CURRENT_BINARY_DIR}/.../BAZ_EXPORT.h -> <prefix>/include/foo/BAZ_EXPORT.h
install(
    FILES "${dvSimMath_export}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/dvsimMath"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooConfig.cmake
#   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)

# }


################################
# Clang tidy Addition 
################################
file(GLOB_RECURSE carl_lib_sources "*.cpp")
if (WITH_CLANG_TIDY)
	add_custom_target(tidy
		COMMAND ${CLANG_TIDY} -p ../../build/compile_commands.json ${CLANG_TIDY_CHECKS} -header-filter='.*' ${carl_lib_sources}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Maths/
	)
	file(GLOB dirs LIST_DIRECTORIES true RELATIVE "${CMAKE_SOURCE_DIR}/Maths/" "*")
  foreach(dir ${dirs})
    message("dir =${dirs}")
		if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/Maths/${dir}")
			file(GLOB_RECURSE sources_${dir} "${CMAKE_SOURCE_DIR}/Maths/${dir}/*.cpp")
			add_custom_target(tidy-${dir}
				COMMAND ${CLANG_TIDY} -p ../../build/compile_commands.json ${CLANG_TIDY_CHECKS} -header-filter='.*' ${sources_${dir}}
				WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Maths/
			)
		endif()
	endforeach()
endif()