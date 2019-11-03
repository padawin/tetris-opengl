#include <iostream>
#include <errno.h>
#include <string.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "renderer.hpp"

GLFWwindow *_window;

void _initGLFW();
bool _createWindow(int window_width, int window_height, const char* title, bool fullscreen);
bool _initGLAD();
void _processInput();

void _initGLFW() {
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

void renderer_main_loop(void (*updateCB)(), void (*renderCB)()) {
	while(!glfwWindowShouldClose(_window)) {
		_processInput();
		(*updateCB)();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		(*renderCB)();
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void _processInput() {
	if (renderer_isKeyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(_window, true);
	}
}

bool renderer_isKeyPressed(const int key) {
	return glfwGetKey(_window, key) == GLFW_PRESS;
}

void renderer_cleanup() {
	glfwTerminate();
}
