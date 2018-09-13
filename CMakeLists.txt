cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(tsp)

#	Enable warnings
add_definitions(-Wall)

#	Set C++17
if (POLICY CMP0025)
	cmake_policy(SET CMP0025 NEW)
endif ()
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "")
# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
# differentiation between debug and release builds.
	set(
		CMAKE_BUILD_TYPE
			"Debug"
		CACHE STRING
			"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or 	CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
		FORCE
	)
endif (CMAKE_BUILD_TYPE STREQUAL "")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions(-O2)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

#	Load headers
file(
	GLOB_RECURSE HEADERS
	${CMAKE_SOURCE_DIR}/src/*.hpp
	${CMAKE_SOURCE_DIR}/src/*.h
)

#	Load source files
file(
	GLOB_RECURSE SOURCES
	${CMAKE_SOURCE_DIR}/src/*.cpp
	${CMAKE_SOURCE_DIR}/src/*.c
)

#	Define the executable
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

#	Dependencies
set(${PROJECT_NAME}_CMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake")

# Define the include DIRs
include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/src
)
