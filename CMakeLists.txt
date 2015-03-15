cmake_minimum_required( VERSION 2.8.4 )
project( CommunityGame_Engine )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file( GLOB_RECURSE SOURCE_FILES "./srcs/**.cpp" )

add_executable( CommunityGame_Engine ${SOURCE_FILES} srcs/AGame.cpp srcs/AGame.hpp srcs/GameObject.cpp srcs/GameObject.hpp srcs/render/RenderEngine.cpp srcs/render/RenderEngine.hpp srcs/AObjectComponent.cpp srcs/AObjectComponent.hpp srcs/math/Vec.tpp srcs/math/Point.tpp srcs/math/Math.cpp srcs/math/Math.hpp)

# GLFW
set( GLFW_VERSION 3.1 )
add_subdirectory( ./libs/glfw-${GLFW_VERSION} )
include_directories( ./libs/glfw-${GLFW_VERSION}/include )
target_link_libraries( CommunityGame_Engine glfw ${GLFW_LIBRARIES} )

# Boost
#set( Boost_VERSION 1.57.0 )
#set( Boost_INCLUDE_DIR ./libs/boost-${Boost_VERSION} )
#set( Boost_LIBRARY_DIR ./libs/boost-${Boost_VERSION}/libs )
#find_package( Boost COMPONENTS system filesystem REQUIRED )
#include_directories( ${Boost_INCLUDE_DIR} )
#link_directories( ${Boost_LIBRARY_DIR} )
#target_link_libraries( CommunityGame_Engine ${Boost_LIBRARIES} )

