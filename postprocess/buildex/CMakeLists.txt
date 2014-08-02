cmake_minimum_required(VERSION 2.6)

# To match Makefiles and have just one build type per configured build
# dir, we collapse VS generator configs to a single choice.
# This must be done prior to the project() command and the var
# must be set in the cache.
if ("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
  if (DEBUG OR "${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
  else ()
    # Go w/ debug info (i#1392)
    set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "" FORCE)
  endif ()
  # we want to use the _LOCATION_<config> property
  string(TOUPPER "${CMAKE_CONFIGURATION_TYPES}" upper)
  set(location_suffix "_${upper}")
else ("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
  set(location_suffix "")
endif ("${CMAKE_GENERATOR}" MATCHES "Visual Studio")

project(buildex)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
if ("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
  # we don't support the Debug and Release subdirs
  foreach (config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${config}" config_upper)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper}
      "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config_upper}
      "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config_upper}
      "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
  endforeach ()
endif ()


include_directories("include")
add_executable(buildex 

src/main.cpp 
src/expression_tree.cpp 
src/node.cpp 
src/canonicalize.cpp 
src/fileparser.cpp 
src/tree_transformations.cpp 

src/build_mem_instrace.cpp 
src/build_mem_dump.cpp
src/build_tree.cpp 
src/build_abs_tree.cpp

src/print_common.cpp 
src/print_halide.cpp 
src/print_dot.cpp 
src/imageparser.cpp

)