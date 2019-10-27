#include "renderer.hpp"

#include <iostream>
#include <errno.h>
#include <string.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

GLFWwindow *_window;

void _initGLFW();
bool _createWindow(int window_width, int window_height, const char* title, bool fullscreen);
bool _initGLAD();
void processInput();

void _initGLFW() {
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
}

bool _createWindow(int window_width, int window_height, const char* title, bool fullscreen) {
	GLFWmonitor* monitor = NULL;
	if (fullscreen) {
		monitor = glfwGetPrimaryMonitor();
	}
	// Create window
	_window = glfwCreateWindow(
		window_width, window_height, title, monitor, NULL
	);
	if (_window == NULL) {
		std::cerr << "Failed to create GLFW window: " << strerror(errno) << std::endl;
		return false;
	}
	glfwMakeContextCurrent(_window);
	return true;
}

bool _initGLAD() {
	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD: " << strerror(errno) << std::endl;
		return false;
	}
	return true;
}

bool renderer_init(int window_width, int window_height, const char* title, bool fullscreen) {
	_initGLFW();
	if (!_createWindow(window_width, window_height, title, fullscreen) || !_initGLAD()) {
		return false;
	}

	// @NOTE This defines the viewport used by OpenGL IN the window, not
	// the position/geometry of the window in the screen.
	glViewport(0, 0, window_width, window_height);
	return true;
}

void renderer_main_loop() {
	while(!glfwWindowShouldClose(_window)) {
		glfwPollEvents();
		processInput();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(_window);
	}
}

void processInput() {
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(_window, true);
	}
}

void renderer_cleanup() {
	glfwTerminate();
}
