#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl3w.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

static void glfw_error_callback(int error, const char* msg)
{
	fprintf(stderr, "GLFW error %d: %s\n", error, msg);
}

int main(void)
{
	glfwSetErrorCallback(glfw_error_callback);

	GLFWwindow* window;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW!\n");
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(
			WINDOW_WIDTH, WINDOW_HEIGHT, 
			"Hacker", nullptr, nullptr);

	if (!window)
	{
		fprintf(stderr, "Failed to create window context!\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	
	if (gl3wInit())
	{
		fprintf(stderr, "Failed to initialize OpenGL!\n");
		return EXIT_FAILURE;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	if (!gl3wIsSupported(3, 2))
	{
		fprintf(stderr, "OpenGL 3.2 not supported on this hardware!\n");
		return EXIT_FAILURE;
	}

	printf("OpenGL %s, shader version %s\n",
			glGetString(GL_VERSION),
			glGetString(GL_SHADING_LANGUAGE_VERSION));

	int fbWidth, fbHeight, winWidth, winHeight;
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	glfwGetWindowSize(window, &winWidth, &winHeight);
	glfwSwapInterval(1);

	float pxr = (float)fbWidth / (float)winWidth;

	printf("Window = %dx%d, framebuffer = %dx%d, pxr = %f\n",
			winWidth, winHeight, fbWidth, fbHeight, pxr);

	NVGcontext* nc = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	bool show_demo_window = true;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glViewport(0, 0, fbWidth, fbHeight);

		// Begin frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		nvgBeginFrame(nc, winWidth, winHeight, pxr);

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// Render frame
		ImGui::Render();

		// End frame
		nvgEndFrame(nc);

		// Swap
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	nvgDeleteGL3(nc);

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}
