project(tsic CXX C)
cmake_minimum_required(VERSION 3.2.2)

enable_testing()

option(BUILD_TESTS "Builds the testing project" OFF)

if(BUILD_TESTS)
	add_subdirectory(tsic_test)
endif()

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMCOnfig.cmake in: ${LLVM_DIR}")

# Warnings
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic")
# Base flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fcolor-diagnostics ")

include_directories("${LLVM_INCLUDE_DIRS}" "${tsic_SOURCE_DIR}/include")
link_directories(${tsic_SOURCE_DIR}/src)
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)

# add_subdirectory(include)
add_subdirectory(lib)

