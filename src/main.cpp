#include <string>
#include <limits.h> // PATH_MAX
#include <stdlib.h> // realpath
#include <libgen.h> // dirname

#include "config.hpp"
#include "renderer.hpp"

const char* WINDOW_TITLE = "Learn OpenGL";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

bool _setBinaryPath(int argc, char* args[]);

void update();
void render();

int main(int argc, char* args[]) {
	if (!_setBinaryPath(argc, args)) {
		return 1;
	}

	bool initOK = renderer_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);

	if (initOK) {
		renderer_main_loop(update, render);
	}

	renderer_cleanup();
	return 0;
}

bool _setBinaryPath(int argc, char* args[]) {
	char binaryPath[PATH_MAX];
	char *res = realpath(dirname(args[argc - argc]), binaryPath);
	if (!res) {
		return false;
	}

	config_setBinPath(binaryPath);
	return true;
}

void update() {

}

void render() {

}
