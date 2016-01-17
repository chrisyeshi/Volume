cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(ENABLE_CUDA ON CACHE BOOL "Enable CUDA modules")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

if(${ENABLE_CUDA})
	add_executable(volumeglcuda volumeglcuda.cpp)
	target_link_libraries(volumeglcuda volume)
	add_test(volumeglcuda volumeglcuda)
endif(${ENABLE_CUDA})
