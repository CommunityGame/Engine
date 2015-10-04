#############################################
# Try to find ASSMIP and set the following: #
#                                           #
# YAML_CPP_FOUND                            #
# YAML_CPP_INCLUDE_DIRS                     #
# YAML_CPP_LIBRARIES                        #
#############################################

SET( YAML_CPP_SEARCH_PATHS
        ${YAML_CPP_ROOT_DIR}				# YAML_CPP!
        ./lib/yaml-cpp
        $ENV{PROGRAMFILES}/YAML_CPP			# WINDOWS
        ~/Library/Frameworks				# MAC
        /Library/Frameworks					# MAC
        /usr/local							# LINUX/MAC/UNIX
        /usr								# LINUX/MAC/UNIX
        /opt								# LINUX/MAC/UNIX
        /sw									# Fink
        /opt/local							# DarwinPorts
        /opt/csw							# Blastwave
        )

FIND_PATH( YAML_CPP_INCLUDE_DIRS
        NAMES
        yaml-cpp/yaml.h
        PATHS
        ${YAML_CPP_SEARCH_PATHS}
        PATH_SUFFIXES
        include
        DOC
        "The directory where GL/glew.h resides"
        )

FIND_LIBRARY( YAML_CPP_LIBRARIES
        NAMES
        libyaml-cpp.a
        PATHS
        ${GLEW_SEARCH_PATHS}
        PATH_SUFFIXES
        lib
        lib64
        lib/Release/Win32
        lib/Release/x64
        DOC
        "The GLEW library"
        )

# Check if we found it!
IF ( YAML_CPP_INCLUDE_DIRS AND YAML_CPP_LIBRARIES )
    SET( YAML_CPP_FOUND TRUE )
    MESSAGE( STATUS "Looking for YAML_CPP - found" )
ELSE ( YAML_CPP_INCLUDE_DIRS AND YAML_CPP_LIBRARIES )
    SET( YAML_CPP_FOUND FALSE )
    MESSAGE( STATUS "Looking for YAML_CPP - not found" )
ENDIF ( YAML_CPP_INCLUDE_DIRS AND YAML_CPP_LIBRARIES )