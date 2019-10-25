#include "renderer.hpp"

const char* WINDOW_TITLE = "Learn OpenGL";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
	bool initOK = renderer_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);

	if (initOK) {
		renderer_main_loop();
	}

	renderer_cleanup();
	return 0;
}
