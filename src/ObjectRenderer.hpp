#ifndef __OBJECT_RENDERER__
#define __OBJECT_RENDERER__

#include <string>
#include <vector>

class ObjectRenderer {
	private:
	unsigned int m_iVAO = 0;
	unsigned int m_iVBO = 0;
	int m_iVerticesCount = 0;
	// Shader program to use
	const char* m_sShaderProgram = "default";

	public:
	void init();
	void setVertices(float* vertices, int verticesCount);
	void render() const;
};

#endif
