cmake_minimum_required(VERSION 3.13.4)
project(cartesian-tree-container)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

flex_target(scanner
  lexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

bison_target(parser
  parser.y
  ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/parser.tab.hh")

add_flex_bison_dependency(scanner parser)

file(GLOB_RECURSE CXX_HEADERS include/*.hpp)
file(GLOB_RECURSE CXX_FILES src/*.cpp src/*.cc)

add_executable(${PROJECT_NAME} 
  main.cc
  ${CXX_HEADERS}
  ${CXX_FILES}
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})