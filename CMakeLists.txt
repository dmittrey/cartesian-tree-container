cmake_minimum_required(VERSION 3.16)
project(syntacore-tools-trial-task)

set(CMAKE_VERBOSE_MAKEFILE OFF)

add_subdirectory(parser)
add_subdirectory(cartesian-tree-container)

add_executable(${PROJECT_NAME} 
  main.cc
)

target_link_libraries(${PROJECT_NAME} PUBLIC parser)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)