##
#   PROJECT
##
cmake_minimum_required( VERSION 2.8.4 )
project( CommunityGame_Engine )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file( GLOB_RECURSE SOURCE_FILES "./srcs/**" )

link_libraries( glfw "${OPENGL_glu_LIBRARY}" )

if ( BUILD_SHARED_LIBS )
    add_definitions(-DGLFW_DLL)
    link_libraries( "${OPENGL_gl_LIBRARY}" "${MATH_LIBRARY}" )
else()
    link_libraries( ${glfw_LIBRARIES} )
endif()

include_directories( "${GLFW_SOURCE_DIR}/include"
                    "${GLFW_SOURCE_DIR}/deps" )

if ( "${OPENGL_INCLUDE_DIR}" )
    include_directories("${OPENGL_INCLUDE_DIR}" )
endif()

set( GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
         "${GLFW_SOURCE_DIR}/deps/glad.c" )

add_executable( CommunityGame_Engine ${SOURCE_FILES} ${GLAD}
tests/main.cpp
tests/Test.cpp
tests/components/Cube.cpp
tests/components/Cube.hpp )

# GLFW
set( GLFW_VERSION 3.1 )
add_subdirectory( ./libs/glfw-${GLFW_VERSION} )
include_directories( ./libs/glfw-${GLFW_VERSION}/include )
target_link_libraries( CommunityGame_Engine glfw ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} )

# LUA
find_package( Lua51 REQUIRED )
include_directories( ${LUA_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${LUA_LIBRARIES} )

# YAML
set( YAML_CPP_VERSION 0.5.2 )
add_subdirectory( ./libs/yaml-cpp-${YAML_CPP_VERSION} )
include_directories( ./libs/yaml-cpp-${YAML_CPP_VERSION}/include )
target_link_libraries( CommunityGame_Engine yaml-cpp ${YAML_CPP_LIBRARIES} )
