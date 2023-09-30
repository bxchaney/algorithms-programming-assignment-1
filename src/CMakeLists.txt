cmake_minimum_required(VERSION 3.10)
project(PA1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Werror;-pedantic-errors;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_compile_options(-Wall -Werror -pedantic-errors -Wextra -Wunused)

add_subdirectory(utils)

add_executable(closest-pairs main.cpp)
add_executable(test-cases tests.cpp)

target_link_libraries(test-cases PUBLIC utils)
