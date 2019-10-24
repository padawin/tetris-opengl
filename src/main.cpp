#include <iostream>
#include <errno.h>
#include <string.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

const char* WINDOW_TITLE = "Learn OpenGL";
const GLuint WINDOW_WIDTH = 800;
const GLuint WINDOW_HEIGHT = 600;
const GLuint GLVIEWPOINT_WIDTH = 800;
const GLuint GLVIEWPOINT_HEIGHT = 600;

int main() {
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	bool initOK = true;
	// Create window
	GLFWwindow *window = glfwCreateWindow(
		WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL
	);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window: " << strerror(errno) << std::endl;
		initOK = false;
	}
	else {
		// @NOTE The context needs to be set BEFORE loading glad
		glfwMakeContextCurrent(window);

		// Init GLAD
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD: " << strerror(errno) << std::endl;
			initOK = false;
		}
	}

	if (initOK) {
		// @NOTE This defines the viewport used by OpenGL IN the window, not
		// the position/geometry of the window in the screen.
		glViewport(0, 0, GLVIEWPOINT_WIDTH, GLVIEWPOINT_HEIGHT);

		while(!glfwWindowShouldClose(window)) {
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	// Cleanup
	glfwTerminate();
	return 0;
}
