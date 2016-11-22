project(tsic CXX C)
cmake_minimum_required(VERSION 3.4.3)

enable_testing()

option(BUILD_TESTS "Builds the testing project" OFF)

if(BUILD_TESTS)
	add_subdirectory(tsic_test)
endif()

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMCOnfig.cmake in: ${LLVM_DIR}")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-rtti")

include_directories("${LLVM_INCLUDE_DIRS}" "${tsic_SOURCE_DIR}/include")
link_directories(${tsic_SOURCE_DIR}/src)
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)

# add_subdirectory(include)
add_subdirectory(lib)
