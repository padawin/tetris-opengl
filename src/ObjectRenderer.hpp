#ifndef __OBJECT_RENDERER__
#define __OBJECT_RENDERER__

#include <string>
#include <vector>

class ObjectRenderer {
	private:
	unsigned int m_iVAO = 0;
	unsigned int m_iVBO = 0;
	unsigned int m_iEBO = 0;
	int m_iIndicesCount = 0;
	// Shader program to use
	const char* m_sShaderProgram = "default";

	public:
	void init();
	void setVertices(float* vertices, unsigned int* indices, int verticesCount, int indicesCount);
	void render() const;
};

#endif
