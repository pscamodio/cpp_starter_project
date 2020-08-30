cmake_minimum_required(VERSION 3.15)

# Allow opt-in to system cmake defined by VCPKG_ROOT
option(USE_VCPKG_ROOT "Use vcpk defined in the VCPKG_ROOT env var" ON)
if (USE_VCPKG_ROOT)
  set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
endif()

# Set the project name to your project name, my project isn't very descriptive
project(myproject VERSION 0.0.0 LANGUAGES CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set all default settings shared by projects, c++ compiler options and warnings
add_library(project_default INTERFACE)
target_compile_features(project_default INTERFACE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    add_compile_definitions(project_default INTERFACE -ftime-trace)
  endif()
endif()

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_default)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_default)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# Shared options for all the subproject
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" OFF)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)

# Add project code
add_subdirectory(src)

# Add integration testing for the entire project
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

# Add fuzzy testing for the entire project
if(ENABLE_FUZZING)
  add_subdirectory(fuzz_test)
endif()

