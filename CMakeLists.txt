##
#   PROJECT
##
cmake_minimum_required( VERSION 2.8.4 )
project( CommunityGame_Engine )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file( GLOB_RECURSE SOURCE_FILES "./srcs/**.cpp" )

add_executable( CommunityGame_Engine ${SOURCE_FILES} tests/main.cpp srcs/math/Quat.tpp)

# GLFW
set( GLFW_VERSION 3.1 )
add_subdirectory( ./libs/glfw-${GLFW_VERSION} )
include_directories( ./libs/glfw-${GLFW_VERSION}/include )
target_link_libraries( CommunityGame_Engine glfw ${GLFW_LIBRARIES} )


##
#   MATH TESTS
##
project( CommunityGame_Math )
add_executable( CommunityGame_Math ${SOURCE_FILES} tests/math.cpp)
target_link_libraries( CommunityGame_Math glfw ${GLFW_LIBRARIES} )