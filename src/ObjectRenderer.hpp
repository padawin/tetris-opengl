#ifndef __OBJECT_RENDERER__
#define __OBJECT_RENDERER__

#include <string>
#include <vector>
#include <glm/glm.hpp>

class ObjectRenderer {
	private:
	unsigned int m_iVAO = 0;
	unsigned int m_iVBO = 0;
	unsigned int m_iEBO = 0;
	int m_iIndicesCount = 0;
	// Shader program to use
	std::string m_sShaderProgram = "default";

	glm::mat4 m_transformMatrix;

	public:
	ObjectRenderer();
	void init();
	void setVertices(float* vertices, unsigned int* indices, int verticesCount, int indicesCount);
	void setShaderProgram(std::string shaderProgram);
	void render() const;
};

#endif
