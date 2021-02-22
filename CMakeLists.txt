cmake_minimum_required(VERSION 3.10)

project("Format Print"
  LANGUAGES CXX
)

find_package(Threads)

# Compile googltest as static lib
add_library(googletest1 STATIC
  googletest/googletest/src/gtest-all.cc
)

target_compile_options(googletest1
  PRIVATE
    "-g" "-O2"
)

target_include_directories(googletest1
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
)

add_executable(testFormatPrint
  testFormatPrint.cc
)

target_include_directories(testFormatPrint
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
)

target_compile_options(testFormatPrint
  PRIVATE
  "-Wall" "-Wextra" "-g" "-fsanitize=address,undefined"
)

target_compile_features(testFormatPrint
  PUBLIC
    cxx_std_17
)

set_target_properties(testFormatPrint
  PROPERTIES
    CXX_EXTENSIONS OFF
    LINK_FLAGS "-fsanitize=address,undefined"
)

target_link_libraries(testFormatPrint
  PRIVATE
    googletest1
    Threads::Threads
)
