cmake_minimum_required(VERSION 3.9.0)

# Name of project
project(niflib)

# Project dependencies
find_package(Threads REQUIRED)
# find_package(Boost REQUIRED)

# CMake Modules
include(TestBigEndian)

# Use glob to get the list of all source files.
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")

# Use glob to get the list of all header files.
file(GLOB_RECURSE LIB_HEADERS "src/*.hpp")

# Project options
option(BUILD_SHARED_LIBS		"Build a shared library."	ON)
option(BUILD_TESTS				"Build tests."				OFF)
#option(BUILD_DOCS				"Build documentation."		OFF)
option(BUILD_EXAMPLES			"Build examples."			OFF)

# Project properties
set(CMAKE_CXX_STANDARD			17)
set(CMAKE_CXX_EXTENSIONS		OFF)
set(CMAKE_CXX_STANDARD_REQUIRED	ON)
set(CMAKE_CXX_VISIBILITY_PRESET	hidden)

# Set project endian type
TEST_BIG_ENDIAN(endian_type)
if(endian_type)
	add_definitions(-DSYSTEM_ENDIAN=0)
else()
	add_definitions(-DSYSTEM_ENDIAN=1)
endif()

# Library additional folders to include
include_directories("include/")

# Library target
add_library(niflib ${LIB_SOURCES} ${LIB_HEADERS})

# Check build settings
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RELEASE)
endif()

# OS & compiler specific options
if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /Yd")
	set(CMAKE_CXX_FLAGS_RELEASE "/Ox")
	set(CMAKE_CXX_FLAGS_RELEASE "/Zi")
else(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

# Option settings
if(BUILD_EXAMPLES)
	# Example program to dump a NIF into human readable text format.
	add_executable(NIFtoText examples/text_dump.cpp)
	target_link_libraries(NIFtoText niflib)

	# Example program to create a copy of a NIF
	add_executable(NIFCopy examples/nif_copy.cpp)
	target_link_libraries(NIFCopy niflib)
endif()

if(BUILD_TESTS)
include(GoogleTest)
	add_subdirectory(lib/googletest)
	enable_testing()
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

	add_executable(GetNifVersionTest test/get_nif_version_test.cpp)
	target_link_libraries(GetNifVersionTest gtest gtest_main)
	target_link_libraries(GetNifVersionTest niflib)

	add_test(get_nif_version GetNifVersionTest "${CMAKE_CURRENT_LIST_DIR}/data/")
endif()