##
#   PROJECT
##
cmake_minimum_required( VERSION 2.8.4 )
project( CommunityGame_Engine )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file( GLOB_RECURSE SOURCE_FILES "./srcs/**" )

file( GLOB_RECURSE TESTS_FILES "./tests/**" )

include( ./cmake/FindYaml-Cpp.cmake )
include( ./cmake/FindOpenVG.cmake )

if ( NOT OPENVG_FOUND )
	message(STATUS "To install OpenVG use this: cd /tmp && git clone git@github.com:procedural/shivavg.git && cd shivavg && cmake . && make && sudo make install")
endif()
if ( NOT Yaml-Cpp_FOUND )
	message(STATUS "To install Yaml-Cpp use this: cd /tmp && git clone git@github.com:jbeder/yaml-cpp.git && cd yaml-cpp && cmake . && make && sudo make install")
endif()

include_directories( "./includes/" )

add_executable( CommunityGame_Engine ${SOURCE_FILES} ${TESTS_FILES} )

# PYTHON
find_package( PythonInterp )
find_package( PythonLibs )
include_directories( ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${PYTHON_LIBRARIES} )

# BOOST
set( BOOST_LIBS
	python
	regex
)

find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED )
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )
include_directories( ${Boost_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${Boost_LIBRARIES} )

# GLFW
find_package( PkgConfig REQUIRED )
pkg_search_module( GLFW REQUIRED glfw3 )
include_directories( ${GLFW_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${GLFW_STATIC_LIBRARIES} )

# YAML
include_directories( ${YAML_CPP_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${YAML_CPP_LIBRARY} )

# OpenVG
include_directories( ${OPENVG_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${OPENVG_LIBRARY} )

# OpenGL
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${OPENGL_LIBRARIES} )

# OpenAL
find_package( OpenAL REQUIRED )
include_directories( ${OPENAL_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${OPENAL_LIBRARY} )

# PYTHON MODULE
add_subdirectory( libs/py_module )
