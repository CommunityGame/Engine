################################################################################
# Try to find OPENVG and set the following:                                    #
#                                                                              #
# OPENVG_FOUND                                                                 #
# OPENVG_INCLUDE_DIR                                                           #
# OPENVG_LIBRARY                                                               #
################################################################################

SET( OPENVG_SEARCH_PATHS
	${OPENVG_ROOT_DIR}					# OPENVG!
	$ENV{PROGRAMFILES}/OPENVG			# WINDOWS
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

FIND_PATH(OPENVG_INCLUDE_DIR
	NAME vg/openvg.h vg/vgu.h
	HINTS
	ENV OPENVG_DIR
	PATH_SUFFIXES include/OPENVG include
	PATHS
	${OPENVG_SEARCH_PATHS}
)

FIND_LIBRARY(OPENVG_LIBRARY
	NAMES libOpenVG OpenVG
	HINTS
	ENV OPENVG_DIR
	PATH_SUFFIXES lib
	PATHS
	${OPENVG_SEARCH_PATHS}
)

# Check if we found it!
IF ( OPENVG_INCLUDE_DIR AND OPENVG_LIBRARY )
	SET( OPENVG_FOUND TRUE )
	MESSAGE( STATUS "Looking for OPENVG - found" )
ELSE ( OPENVG_INCLUDE_DIR AND OPENVG_LIBRARY )
	SET( OPENVG_FOUND FALSE )
	MESSAGE( STATUS "Looking for OPENVG - not found" )
ENDIF ( OPENVG_INCLUDE_DIR AND OPENVG_LIBRARY )
