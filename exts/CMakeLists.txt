#--------------------------------------------------------------------------
# exts
#--------------------------------------------------------------------------

ADD_LIBRARY(exts INTERFACE)

ADD_SUBDIRECTORY(glfw)
ADD_SUBDIRECTORY(gl3w)

TARGET_LINK_LIBRARIES(exts INTERFACE glfw gl3w)
