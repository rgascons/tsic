project(tsic CXX C)
cmake_minimum_required(VERSION 3.4.3)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMCOnfig.cmake in: ${LLVM_DIR}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti")

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${tsic_SOURCE_DIR}/src)
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)

add_executable(tsic src/main.cpp src/Error.cpp src/Lexer.cpp src/Parser.cpp src/AST.cpp)

target_link_libraries(tsic ${llvm_libs})