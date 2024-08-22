cmake_minimum_required(VERSION 3.1)
project(volumetric_plugin)

set(CMAKE_CXX_STANDARD 11)

find_package(AMBF)
find_package(Boost COMPONENTS program_options filesystem)

include_directories(${AMBF_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

link_directories(${AMBF_LIBRARY_DIRS})

add_definitions(${AMBF_DEFINITIONS})

set(vol_plugin_prefix "src")

add_library(volumetric_drilling SHARED
    ${vol_plugin_prefix}/simulator_plugin.cpp
    ${vol_plugin_prefix}/simulator_plugin.h)

target_link_libraries(volumetric_drilling ${Boost_LIBRARIES} ${AMBF_LIBRARIES})
set_property(TARGET volumetric_drilling PROPERTY POSITION_INDEPENDENT_CODE TRUE)
