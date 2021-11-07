#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl3w.h>

#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

int main(void)
{
	GLFWwindow* window;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return EXIT_FAILURE;
	}

	window = glfwCreateWindow(
			WINDOW_WIDTH, WINDOW_HEIGHT, 
			"Hacker", nullptr, nullptr);

	if (!window)
	{
		fprintf(stderr, "Failed to create window context\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	
	if (gl3wInit())
	{
		fprintf(stderr, "Failed to initialize OpenGL!\n");
		return EXIT_FAILURE;
	}

	if (!gl3wIsSupported(3, 2))
	{
		fprintf(stderr, "OpenGL 3.2 not supported on this hardware!\n");
		return EXIT_FAILURE;
	}

	printf("OpenGL %s, shader version %s\n",
			glGetString(GL_VERSION),
			glGetString(GL_SHADING_LANGUAGE_VERSION));

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return EXIT_SUCCESS;
}
