cmake_minimum_required(VERSION 3.16)
project(cartesian-tree-container)

add_library(
    ${PROJECT_NAME} 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cartesian_tree.hpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/cartesian_tree.cc"
    )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

