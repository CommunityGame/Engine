##
#   PROJECT
##
cmake_minimum_required( VERSION 2.8.4 )
project( CommunityGame_Engine )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file( GLOB_RECURSE SOURCE_FILES "./srcs/**" )

file( GLOB_RECURSE TESTS_FILES "./tests/**" )

include( ./cmake/FindYaml-Cpp.cmake )
include( ./cmake/FindGLFW3.cmake )
include( ./cmake/FindOpenVG.cmake )

include_directories( "./includes/" )

add_executable( CommunityGame_Engine ${SOURCE_FILES} ${TESTS_FILES} )

# PYTHON
# set( Python_ADDITIONAL_VERSIONS 3.4 )
find_package( PythonInterp )
find_package( PythonLibs )
include_directories( ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} )

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
include_directories( ${GLFW3_INCLUDE_DIR} )
target_link_libraries( CommunityGame_Engine ${GLFW3_LIBRARY} )

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
