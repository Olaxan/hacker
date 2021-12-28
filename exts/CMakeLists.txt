#--------------------------------------------------------------------------
# exts
#--------------------------------------------------------------------------

ADD_LIBRARY(exts INTERFACE)

# GLFW, GL3W (has CMakeLists)
ADD_SUBDIRECTORY(glfw)
ADD_SUBDIRECTORY(gl3w)

# NanoVG
ADD_LIBRARY(nanovg STATIC
	nanovg/src/nanovg.c
	nanovg/src/nanovg.h
	nanovg/src/nanovg_gl.h
	nanovg/src/nanovg_gl_utils.h)

# ImGUI
ADD_LIBRARY(imgui STATIC 
	imgui/imgui_internal.h 
	imgui/imgui.h 
	imgui/imgui.cpp
	imgui/imgui_demo.cpp 
	imgui/imgui_draw.cpp 
	imgui/imgui_tables.cpp
	imgui/imgui_widgets.cpp
	imgui/backends/imgui_impl_glfw.h
	imgui/backends/imgui_impl_glfw.cpp
	imgui/backends/imgui_impl_opengl3.h
	imgui/backends/imgui_impl_opengl3.cpp
	imgui/backends/imgui_impl_opengl3_loader.h)

TARGET_LINK_LIBRARIES(imgui PUBLIC exts)
TARGET_INCLUDE_DIRECTORIES(imgui PUBLIC 
	imgui imgui/backends imgui/examples/example_glfw_opengl3)

TARGET_LINK_LIBRARIES(nanovg PUBLIC exts)
TARGET_INCLUDE_DIRECTORIES(nanovg PUBLIC nanovg/src)

# Link against external interface
TARGET_LINK_LIBRARIES(exts INTERFACE glfw gl3w nanovg imgui)
