cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
# find_package(HDF5 NAMES hdf5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIR})

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)
file(GLOB UI_FILES *.ui)

qt5_wrap_ui(UI_HEADERS ${UI_FILES})
add_library(volume ${SOURCES} ${HEADERS} ${UI_HEADERS})
target_compile_features(volume PUBLIC cxx_nullptr)
target_link_libraries(volume ${HDF5_LIBRARIES})
qt5_use_modules(volume Core Widgets)
