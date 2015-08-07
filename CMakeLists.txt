##
#   PROJECT
##
cmake_minimum_required( VERSION 2.8.4 )
project( CommunityGame_Engine )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

file( GLOB_RECURSE SOURCE_FILES "./srcs/**" )

file( GLOB_RECURSE TESTS_FILES "./tests/**" )

add_executable( CommunityGame_Engine ${SOURCE_FILES} ${TESTS_FILES} )

# PYTHON
set( Python_ADDITIONAL_VERSIONS 3.4 )
find_package( PythonLibs 3.4 REQUIRED )
include_directories( ${PYTHON_INCLUDE_DIRS} )
target_link_libraries( CommunityGame_Engine ${PYTHON_LIBRARIES} )

# BOOST
set( BOOST_LIBS
	python-py34
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

#file( COPY ./resources DESTINATION . )