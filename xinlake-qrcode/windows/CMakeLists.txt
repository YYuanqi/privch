# The Flutter tooling requires that developers have a version of Visual Studio
# installed that includes CMake 3.14 or later. You should not increase this
# version, as doing so will cause the plugin to fail to compile for some
# customers of the plugin.
cmake_minimum_required(VERSION 3.14)

# Project-level configuration.
set(PROJECT_NAME "xinlake_qrcode")
project(${PROJECT_NAME} LANGUAGES CXX)

# zxing cpp
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../cpp/zxing-core" zxing-cpp EXCLUDE_FROM_ALL)

# This value is used when generating builds using this plugin, so it must
# not be changed
set(PLUGIN_NAME "xinlake_qrcode_plugin")

list(APPEND PLUGIN_SOURCES
  "xinlake_qrcode_plugin.h"
  "xinlake_qrcode_plugin.cpp"
  "zxing_reader.cpp"
)

# Define the plugin library target. Its name must not be changed (see comment
# on PLUGIN_NAME above).
add_library(${PLUGIN_NAME} SHARED
  "include/xinlake_qrcode/xinlake_qrcode_plugin_c_api.h"
  "xinlake_qrcode_plugin_c_api.cpp"
  ${PLUGIN_SOURCES}
)

# Apply a standard set of build settings that are configured in the
# application-level CMakeLists.txt. This can be removed for plugins that want
# full control over build settings.
apply_standard_settings(${PLUGIN_NAME})

# Symbols are hidden by default to reduce the chance of accidental conflicts
# between plugins. This should not be removed; any symbols that should be
# exported should be explicitly exported with the FLUTTER_PLUGIN_EXPORT macro.
set_target_properties(${PLUGIN_NAME} PROPERTIES
  CXX_VISIBILITY_PRESET hidden)
target_compile_definitions(${PLUGIN_NAME}
  PRIVATE FLUTTER_PLUGIN_IMPL)

# Source include directories and library dependencies. Add any plugin-specific
# dependencies here.
target_include_directories(${PLUGIN_NAME}
  INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
  
  # to compile plugin cpp files
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../cpp/stb"
)

# Xinalke
# There are warnings for stb-image package when compiling at W4 level. 
target_compile_options(${PLUGIN_NAME} PRIVATE /W3 /WX /wd4100)

target_link_libraries(${PLUGIN_NAME}
  PRIVATE flutter flutter_wrapper_plugin ZXing
)

# List of absolute paths to libraries that should be bundled with the plugin.
# This list could contain prebuilt libraries, or libraries created by an
# external build triggered from this build file.
set(xinlake_qrcode_bundled_libraries
  ""
  PARENT_SCOPE
)
