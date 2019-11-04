#include "Triangle.hpp"
#include "opengl/ObjectRenderer.hpp"

void Triangle::init() {
	float vertices[] = {
		// vertices       // texture
		0.5f, 1.0f, 0.0f, 0.5f, 1.0f, // top
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f  // bottom left
	};
	unsigned int indices[] = {
		0, 1, 2,
	};
	m_renderer = std::shared_ptr<GameObjectRenderer>(new ObjectRenderer());
	ObjectRenderer *renderer = (ObjectRenderer *) m_renderer.get();

	renderer->init();
	renderer->setShaderProgram("default");
	renderer->setTexture("wall.jpg");
	renderer->setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
}
