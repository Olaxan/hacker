#include <GLFW/glfw3.h>

#include <stdlib.h>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return EXIT_FAILURE;

	window = glfwCreateWindow(
			WINDOW_WIDTH, WINDOW_HEIGHT, 
			"Hacker", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
