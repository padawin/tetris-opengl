#include "renderers.hpp"

void renderer_initSideRenderer(ObjectRenderer *renderer, int height) {
	float top = (float) height / 2;
	float bottom = (float) height / -2;
	float vertices[] = {
		// vertices       // texture
		 0.5f, top, 0.5f, 1.0f, (float) height, // top right
		-0.5f, top, 0.5f, 0.0f, (float) height, // top left
		 0.5f, bottom, 0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, bottom, 0.5f, 0.0f, 0.0f, // bottom left

		// back
		 0.5f, top, -0.5f, 1.0f, (float) height, // top right
		-0.5f, top, -0.5f, 0.0f, (float) height, // top left
		 0.5f, bottom, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, bottom, -0.5f, 0.0f, 0.0f, // bottom left

		// left
		-0.5f, top, 0.5f, 0.0f, (float) height,
		-0.5f, bottom, 0.5f, 0.0f, 0.0f,
		-0.5f, top, -0.5f, 0.0f, (float) height,
		-0.5f, bottom, -0.5f, 0.0f, 0.0f,

		// right
		 0.5f, top, 0.5f, 1.0f, (float) height,
		 0.5f, bottom, 0.5f, 1.0f, 0.0f,
		 0.5f, top, -0.5f, 1.0f, (float) height,
		 0.5f, bottom, -0.5f, 1.0f, 0.0f,

		 // up
		 0.5f, top, 0.5f, 1.0f, (float) height,
		-0.5f, top, 0.5f, 0.0f, (float) height,
		 0.5f, top, -0.5f, 1.0f, (float) height,
		-0.5f, top, -0.5f, 0.0f, (float) height,

		// bottom
		 0.5f, bottom, 0.5f, 1.0f, 0.0f,
		 0.5f, bottom, 0.5f, 1.0f, 0.0f,
		-0.5f, bottom, -0.5f, 0.0f, 0.0f,
		-0.5f, bottom, -0.5f, 0.0f, 0.0f
	};
	unsigned int indices[] = { // note that we start from 0!
		0, 1, 2, // first triangle
		1, 2, 3, // second triangle

		4, 5, 6,
		5, 6, 7,

		8, 9, 10,
		9, 10, 11,

		12, 13, 14,
		13, 14, 15,

		16, 17, 18,
		17, 18, 19,

		20, 21, 22,
		21, 22, 23
	};

	renderer->init();
	renderer->setShaderProgram("boardcell");
	renderer->setTexture("piece.png");
	renderer->setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
}

void renderer_initPieceRenderer(ObjectRenderer *renderer) {
	float vertices[] = {
		// front
		// vertices        // texture
		 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top right
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top left
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom left

		// back
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top right
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top left
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left

		// left
		-0.5f,  0.5f, 0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		// right
		 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,

		 // up
		 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

		// bottom
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2, // first triangle
		1, 2, 3, // second triangle

		4, 5, 6,
		5, 6, 7,

		8, 9, 10,
		9, 10, 11,

		12, 13, 14,
		13, 14, 15,

		16, 17, 18,
		17, 18, 19,

		20, 21, 22,
		21, 22, 23
	};

	renderer->init();
	renderer->setShaderProgram("default");
	renderer->setTexture("piece.png");
	renderer->setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
}
