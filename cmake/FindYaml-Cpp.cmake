################################################################################
# Try to find YAML_CPP and set the following:                                  #
#                                                                              #
# YAML_CPP_FOUND                                                               #
# YAML_CPP_INCLUDE_DIR                                                         #
# YAML_CPP_LIBRARY                                                             #
################################################################################

SET( YAML_CPP_SEARCH_PATHS
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

FIND_PATH(YAML_CPP_INCLUDE_DIR
	NAMES yaml-cpp/yaml.h yaml.h
	HINTS
	ENV YAML_CPP_DIR
	PATH_SUFFIXES include/YAML_CPP include
	PATHS
	${YAML_CPP_SEARCH_PATHS}
)

FIND_LIBRARY(YAML_CPP_LIBRARY
	NAMES libyaml-cpp yaml-cpp
	HINTS
	ENV YAML_CPP_DIR
	PATH_SUFFIXES lib
	PATHS
	${YAML_CPP_SEARCH_PATHS}
)

# Check if we found it!
IF ( YAML_CPP_INCLUDE_DIR AND YAML_CPP_LIBRARY )
	SET( YAML_CPP_FOUND TRUE )
	MESSAGE( STATUS "Looking for YAML_CPP - found" )
ELSE ( YAML_CPP_INCLUDE_DIR AND YAML_CPP_LIBRARY )
	SET( YAML_CPP_FOUND FALSE )
	MESSAGE( STATUS "Looking for YAML_CPP - not found" )
ENDIF ( YAML_CPP_INCLUDE_DIR AND YAML_CPP_LIBRARY )
