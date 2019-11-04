#include "Rectangle.hpp"
#include "opengl/ObjectRenderer.hpp"

void Rectangle::init() {
	float vertices[] = {
		// vertices        // texture
		 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
		 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-1.0f, 0.0f, 0.0f, 0.0f, 0.0f  // bottom left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		1, 2, 3    // second triangle
	};
	m_renderer = std::shared_ptr<GameObjectRenderer>(new ObjectRenderer());
	ObjectRenderer *renderer = (ObjectRenderer *) m_renderer.get();

	renderer->init();
	renderer->setShaderProgram("default");
	renderer->setTexture("container.jpg");
	renderer->setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
}
