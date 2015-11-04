##
#   PROJECT
##
cmake_minimum_required( VERSION 2.8.4 )
project( CommunityGame_Engine )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file( GLOB_RECURSE SOURCE_FILES "./srcs/**" )

file( GLOB_RECURSE TESTS_FILES "./tests/**" )

include( ./cmake/FindYaml-Cpp.cmake )

include_directories( "./includes/" )

# GLAD
set( GLAD "./libs/glad/glad.c")
add_executable( CommunityGame_Engine ${SOURCE_FILES} ${GLAD} ${TESTS_FILES} )

# PYTHON
set( Python_ADDITIONAL_VERSIONS 3.4 )
find_package( PythonLibs )
include_directories( ${PYTHON_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${PYTHON_LIBRARIES} )

# BOOST
set( BOOST_LIBS
	python-py34
	regex
)
set( BOOST_VERSION 1.58.0 )

find_package(Boost ${BOOST_VERSION} COMPONENTS ${BOOST_LIBS} REQUIRED )
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )
include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${Boost_LIBRARIES} )

# GLFW
find_package( PkgConfig REQUIRED )
pkg_search_module( GLFW REQUIRED glfw3 )
include_directories( ${GLFW_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${GLFW_STATIC_LIBRARIES} )

# YAML
include_directories( ${YAML_CPP_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${YAML_CPP_LIBRARIES} )

# OpenGL
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${OPENGL_LIBRARIES} )

# OpenAL
find_package( OpenAL REQUIRED )
include_directories( ${OPENAL_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${OPENAL_LIBRARY} )

# OpenVG
find_library( OpenVG_Lib NAMES OpenVG PATHS ./libs/ )
target_link_libraries( CommunityGame_Engine ${OpenVG_Lib} )

# PYTHON MODULE
add_subdirectory( libs/py_module )