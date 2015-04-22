cmake_minimum_required(VERSION 2.8.11)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(HDF5 NAMES hdf5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIR})

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)
file(GLOB UI_FILES *.ui)

qt5_wrap_ui(UI_HEADERS ${UI_FILES})
add_library(volume ${SOURCES} ${HEADERS} ${UI_HEADERS})
qt5_use_modules(volume Core Widgets)
target_link_libraries(volume ${HDF5_LIBRARIES})
