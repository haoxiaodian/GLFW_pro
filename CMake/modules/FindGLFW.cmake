
SET(GLFW_DIR "" CACHE PATH "Set to base GLFW install path")
MACRO( FIND_GLFW_INCLUDE THIS_GLFW_INCLUDE_DIR THIS_GLFW_INCLUDE_FILE )

FIND_PATH( ${THIS_GLFW_INCLUDE_DIR} ${THIS_GLFW_INCLUDE_FILE}
    PATHS
        ${GLFW_DIR}
        $ENV{GLFW_SOURCE_DIR}
        $ENV{GLFWDIR}
        $ENV{GLFW_DIR}
        /usr/local/
        /usr/
        /sw/ # Fink
        /opt/local/ # DarwinPorts
        /opt/csw/ # Blastwave
        /opt/
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;GLFW_ROOT]/
        ~/Library/Frameworks
        /Library/Frameworks
    PATH_SUFFIXES
        /include/
)

ENDMACRO( FIND_GLFW_INCLUDE THIS_GLFW_INCLUDE_DIR THIS_GLFW_INCLUDE_FILE )


FIND_GLFW_INCLUDE( GLFW_INCLUDE_DIR       glfw3.h)

###### libraries ######

MACRO( FIND_GLFW_LIBRARY MYLIBRARY MYLIBRARYNAME )

FIND_LIBRARY(${MYLIBRARY}
    NAMES
        ${MYLIBRARYNAME}
    PATHS
        ${GLFW_DIR}
        $ENV{GLFW_BUILD_DIR}
        $ENV{GLFW_DIR}
        $ENV{GLFWDIR}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;GLFW_ROOT]/lib
        /usr/freeware
    PATH_SUFFIXES
        /lib/
        /lib64/
        /build/lib/
        /build/lib64/
        /Build/lib/
        /Build/lib64/
     )

ENDMACRO(FIND_GLFW_LIBRARY LIBRARY LIBRARYNAME)

FIND_GLFW_LIBRARY( GLFW_DEBUG_LIBRARIES glfw3)

FIND_GLFW_LIBRARY( GLFW_RELEASE_LIBRARIES glfw3)


SET( GLFW_FOUND "NO" )
IF( GLFW_DEBUG_LIBRARIES AND GLFW_INCLUDE_DIR )
    SET( GLFW_FOUND "YES" )
    SET( GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
    GET_FILENAME_COMPONENT( GLFW_LIBRARIES_DIR ${GLFW_DEBUG_LIBRARIES} PATH )
ENDIF( GLFW_DEBUG_LIBRARIES AND GLFW_INCLUDE_DIR )


