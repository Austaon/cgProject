cmake_minimum_required(VERSION 3.2)
project(cgProject)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


if( APPLE )
    set(CMAKE_CXX_FLAGS "-framework OpenGL -framework GLUT")
endif()

set(SOURCE_FILES
    source/lodepng.h
    source/lodepng.cpp
    source/imageWriter.h
    source/main.cpp
    source/matrix.h
    source/KdTree.h
    source/KdTree.cpp
    source/mesh.cpp
    source/mesh.h
    source/raytracing.cpp
    source/raytracing.h
    source/traqueboule.h
    source/Vec3D.h
    source/Vertex.h)

add_executable(cgProject ${SOURCE_FILES})