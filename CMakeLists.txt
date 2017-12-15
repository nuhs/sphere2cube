cmake_minimum_required(VERSION 2.8)

project( Sphere2Cube )

set (CMAKE_CXX_STANDARD 11)
include(flags.c++.std.cmake)
include_directories( ${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )

find_package( OpenCV 3 REQUIRED )
add_executable( sphere2cube main.cpp sphere2cube.cpp )
target_link_libraries( sphere2cube ${OpenCV_LIBS} )
