################################################################################
# Try to find GLFW3 and set the following:                                     #
#                                                                              #
# GLFW3_FOUND                                                                  #
# GLFW3_INCLUDE_DIR                                                            #
# GLFW3_LIBRARY                                                                #
################################################################################

SET( GLFW3_SEARCH_PATHS
	${YAML_CPP_ROOT_DIR}				# YAML_CPP!
	$ENV{PROGRAMFILES}/YAML_CPP			# WINDOWS
	~/Library/Frameworks				# MAC
	/Library/Frameworks					# MAC
	/usr/local							# LINUX/MAC/UNIX
	/usr								# LINUX/MAC/UNIX
	/opt								# LINUX/MAC/UNIX
	/sw									# Fink
	/opt/local							# DarwinPorts
	/opt/csw							# Blastwave
	./lib
	./libs
)

FIND_PATH(GLFW3_INCLUDE_DIR
	NAME GLFW/glfw3.h
	HINTS
	ENV GLFW3_DIR
	PATH_SUFFIXES include/GLFW include
	PATHS
	${GLFW3_SEARCH_PATHS}
)

FIND_LIBRARY(GLFW3_LIBRARY
	NAMES glfw3 libglfw3 glfw
	HINTS
	ENV GLFW3_DIR
	PATH_SUFFIXES lib
	PATHS
	${GLFW3_SEARCH_PATHS}
)

# Check if we found it!
IF ( GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY )
	SET( GLFW3_FOUND TRUE )
	MESSAGE( STATUS "Looking for GLFW3 - found" )
ELSE ( GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY )
	SET( GLFW3_FOUND FALSE )
	MESSAGE( STATUS "Looking for GLFW3 - not found" )
ENDIF ( GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY )
