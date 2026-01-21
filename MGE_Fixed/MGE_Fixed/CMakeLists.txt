cmake_minimum_required(VERSION 3.26)
project(MGE_CLion)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCES
        mge/*.h
        mge/*.cpp
)

add_executable(MGE_CLion ${SOURCE_FILES} ${SOURCES}
        glm.hpp main.cpp)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(MGE_CLion PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
find_package(GLEW REQUIRED)
target_link_libraries(MGE_CLion PRIVATE GLEW::GLEW)
