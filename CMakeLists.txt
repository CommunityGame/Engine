cmake_minimum_required(VERSION 2.8.4)
project(CommunityGame_Engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES
    "./srcs/*.cpp"
)

add_executable(CommunityGame_Engine ${SOURCE_FILES})

# GLFW
add_subdirectory(./libs/glfw)
include_directories(./libs/glfw/include)
target_link_libraries(CommunityGame_Engine glfw ${GLFW_LIBRARIES})
target_link_libraries(CommunityGame_Engine glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

