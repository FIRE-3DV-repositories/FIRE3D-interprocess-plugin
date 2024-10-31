cmake_minimum_required(VERSION 3.1)
project(FIRE3D_interprocess_plugin)

set(CMAKE_CXX_STANDARD 11)

find_package(AMBF)
find_package(Boost COMPONENTS program_options filesystem)

include_directories(${AMBF_INCLUDE_DIRS})

link_directories(${AMBF_LIBRARY_DIRS})

add_definitions(${AMBF_DEFINITIONS})

set(vol_plugin_prefix "src")

add_library(FIRE3D_interprocess SHARED
    ${vol_plugin_prefix}/simulator_plugin.cpp
    ${vol_plugin_prefix}/simulator_plugin.h)

set_property(TARGET FIRE3D_interprocess PROPERTY POSITION_INDEPENDENT_CODE TRUE)
target_link_libraries(FIRE3D_interprocess ${AMBF_LIBRARIES})
set(INTERPROCESS_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/boost)
target_include_directories(FIRE3D_interprocess PUBLIC ${INTERPROCESS_INCLUDE_DIR} ${CMAKE_CURRENT_LIST_DIR}/lib)
target_compile_definitions(FIRE3D_interprocess PUBLIC BOOST_DATE_TIME_NO_LIB)

set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/glm/glm)
target_include_directories(FIRE3D_interprocess PUBLIC ${GLM_INCLUDE_DIR})
add_definitions(-DGLM_FORCE_DEPTH_ZERO_TO_ONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
