# initialize project
cmake_minimum_required(VERSION 3.10.0)
project(Lander)

# compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# load packages
set(CMAKE_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS graphics window system)

# headers directories
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})
include_directories(usr/local/include/)

# project directories
include_directories(headers)

# project sources
file(GLOB SRC src/**/*.cpp src/*.cpp)

# create exectuables
add_executable(Lander ${SRC})

# link libraries
target_link_libraries(Lander ${OPENGL_LIBRARIES})
target_link_libraries(Lander ${SFML_LIBRARIES} ${SFML_DPENDENCIES})
target_link_libraries(Lander /usr/local/lib/Box2d/libBox2D.a)
