cmake_minimum_required(VERSION 3.16)
project(cartesian-tree-container)

add_library(
    ${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cartesian_tree.hpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cartesian_node.hpp" 
    )

target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

