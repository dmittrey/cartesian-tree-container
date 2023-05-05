cmake_minimum_required(VERSION 3.16)
project(syntacore-tools-intership-task)

add_subdirectory(parser)
add_subdirectory(cartesian-tree-container)

add_executable(${PROJECT_NAME} main.cc)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} PRIVATE cartesian-tree-container)
target_link_libraries(${PROJECT_NAME} PRIVATE parser)