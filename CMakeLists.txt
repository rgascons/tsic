cmake_minimum_required(VERSION 3.4.3)
project(tsic-dist)

enable_testing()

option(BUILD_TSIC "Builds TSIC project" ON)
option(BUILD_TESTS "Builds the testing project" OFF)

if(BUILD_TSIC)
	add_subdirectory(tsic)
endif()

if(BUILD_TESTS)
	add_subdirectory(tsic_test)
endif()