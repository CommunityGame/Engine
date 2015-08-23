##
#   PROJECT
##
cmake_minimum_required( VERSION 2.8.4 )
project( CommunityGame_Engine )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file( GLOB_RECURSE SOURCE_FILES "./srcs/**" )

file( GLOB_RECURSE TESTS_FILES "./tests/**" )



include_directories( "./libs/glfw-3.1/include"
                    "./libs/glfw-3.1/deps" )

set( GLAD "./libs/glfw-3.1/deps/glad/glad.h"
         "./libs/glfw-3.1/deps/KHR/khrplatform.h"
         "./libs/glfw-3.1/deps/glad.c" )

add_executable( CommunityGame_Engine ${SOURCE_FILES} ${GLAD} ${TESTS_FILES} )

# PYTHON
set( Python_ADDITIONAL_VERSIONS 3.4 )
find_package( PythonLibs 3.4 REQUIRED )
include_directories( ${PYTHON_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${PYTHON_LIBRARIES} )

# BOOST
set( BOOST_LIBS
	python-py34
	regex
)
set( BOOST_VERSION 1.55.0 )

find_package(Boost ${BOOST_VERSION} COMPONENTS ${BOOST_LIBS} REQUIRED )
if ( Boost_FOUND )
	include_directories( ${Boost_INCLUDE_DIRS} )
	set( Boost_USE_STATIC_LIBS OFF )
	set( Boost_USE_MULTITHREADED ON )
	set( Boost_USE_STATIC_RUNTIME OFF )

	target_link_libraries( CommunityGame_Engine ${Boost_LIBRARIES} )
elseif( NOT Boost_FOUND )
	message(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
endif()

# PYTHON MODULE
add_subdirectory( ./resources/modules/lib_module )

# GLFW
find_package( PkgConfig REQUIRED )
pkg_search_module( GLFW REQUIRED glfw3 )
include_directories( ${GLFW_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${GLFW_STATIC_LIBRARIES} )

# YAML
set( YAML_CPP_VERSION 0.5.2 )
set( YAML_CPP_BUILD_TOOLS OFF )
add_subdirectory( ./libs/yaml-cpp-${YAML_CPP_VERSION} )
include_directories( ./libs/yaml-cpp-${YAML_CPP_VERSION}/include )
target_link_libraries( CommunityGame_Engine yaml-cpp ${YAML_CPP_LIBRARIES} )

# XML
set( RAPIDXML_VERSION 1.13 )
include_directories( ./libs/rapidxml-${RAPIDXML_VERSION} )

# GLM
set( GLM_VERSION 0.9.7.0 )
include_directories( ./libs/glm-${GLM_VERSION} )

# NANO_SVG
#include_directories( ./libs/svgpp )

# GLU for OpenVG
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${OPENGL_LIBRARIES} )
#find_package( GLEW REQUIRED )
#include_directories( ${GLEW_INCLUDE_DIRS} )
#target_link_libraries( CommunityGame_Engine ${GLEW_LIBRARIES} )
#find_package( GLUT REQUIRED )
#include_directories( ${GLUT_INCLUDE_DIRS} )
#target_link_libraries( CommunityGame_Engine ${GLUT_LIBRARIES} )

#include_directories( ./libs/glfw-3.1/deps/ )

# OpenVG
#file( COPY ./libs/libOpenVG.so DESTINATION /usr/local/lib )
include_directories( /usr/local/includes/ )
find_library( OpenVG_Lib NAMES OpenVG PATHS /usr/local/lib/ )
target_link_libraries( CommunityGame_Engine ${OpenVG_Lib} )
#include_directories( includes/ )
#find_library( ShivaVG_Lib NAMES ShivaVG PATHS ./libs/ )
#target_link_libraries( CommunityGame_Engine ${ShivaVG_Lib} )