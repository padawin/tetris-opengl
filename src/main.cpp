#include <string>
#include <limits.h> // PATH_MAX
#include <stdlib.h> // realpath
#include <libgen.h> // dirname

#include "game/config.hpp"

#include "opengl/renderer.hpp"
#include "opengl/shader.hpp"
#include "opengl/texture.hpp"

#include "game/Game.hpp"

const char* WINDOW_TITLE = "Learn OpenGL";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

bool _setBinaryPath(int argc, char* args[]);

void update();
void render();

Game game;

int main(int argc, char* args[]) {
	if (!_setBinaryPath(argc, args)) {
		return 1;
	}

	bool initOK = (
		renderer_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false)
		&& shader_loadPrograms()
		&& texture_loadAll()
	);

	if (initOK && game.init()) {
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
	game.update();
}

void render() {
	game.render();
}
