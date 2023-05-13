cmake_minimum_required(VERSION 3.16)
project(syntacore-tools-intership-task)

set(CMAKE_CXX_STANDARD 17)

# add_subdirectory(parser)
add_subdirectory(cartesian-tree-container)
add_subdirectory(google-tests)

add_executable(${PROJECT_NAME} main.cc)

target_link_libraries(${PROJECT_NAME} PRIVATE cartesian-tree-container)
# target_link_libraries(${PROJECT_NAME} PRIVATE parser)

enable_testing()

add_executable(
  tests
  "google-tests/node_tests.cc"
  "google-tests/tree_tests.cc"
)
target_link_libraries(
  tests
  GTest::gtest_main
  cartesian-tree-container
)

include(GoogleTest)
gtest_discover_tests(tests)