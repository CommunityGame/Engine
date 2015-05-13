##
#   PROJECT
##
cmake_minimum_required( VERSION 2.8.4 )
project( CommunityGame_Engine )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file( GLOB_RECURSE SOURCE_FILES "./srcs/**" )

link_libraries(glfw "${OPENGL_glu_LIBRARY}")

if (BUILD_SHARED_LIBS)
    add_definitions(-DGLFW_DLL)
    link_libraries("${OPENGL_gl_LIBRARY}" "${MATH_LIBRARY}")
else()
    link_libraries(${glfw_LIBRARIES})
endif()

include_directories("${GLFW_SOURCE_DIR}/include"
                    "${GLFW_SOURCE_DIR}/deps")

if ("${OPENGL_INCLUDE_DIR}")
    include_directories("${OPENGL_INCLUDE_DIR}")
endif()

set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
         "${GLFW_SOURCE_DIR}/deps/glad.c")
set(GETOPT "${GLFW_SOURCE_DIR}/deps/getopt.h"
           "${GLFW_SOURCE_DIR}/deps/getopt.c")
set(TINYCTHREAD "${GLFW_SOURCE_DIR}/deps/tinycthread.h"
                "${GLFW_SOURCE_DIR}/deps/tinycthread.c")

add_executable( CommunityGame_Engine ${SOURCE_FILES} ${GLAD}
tests/main.cpp
tests/Test.cpp)

# GLFW
set( GLFW_VERSION 3.1 )
add_subdirectory( ./libs/glfw-${GLFW_VERSION} )
include_directories( ./libs/glfw-${GLFW_VERSION}/include )

target_link_libraries( CommunityGame_Engine glfw ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} )

##
#   MATH TESTS
##
#project( CommunityGame_Math )
#add_executable( CommunityGame_Math ${SOURCE_FILES} tests/math.cpp)
#target_link_libraries( CommunityGame_Math glfw ${GLFW_LIBRARIES} )