#include <iostream>
#include "ObjectRenderer.hpp"
#include "glad/glad.h"
#include "shader.hpp"

void ObjectRenderer::init() {
	glGenVertexArrays(1, &m_iVAO);
	glGenBuffers(1, &m_iVBO);
	glGenBuffers(1, &m_iEBO);
}

void ObjectRenderer::setVertices(float* vertices, unsigned int* indices, int verticesSize, int indicesSize) {
	m_iIndicesCount = indicesSize / (int) sizeof(unsigned int);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(m_iVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize , vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void ObjectRenderer::render() const {
	glUseProgram(shader_getProgram(m_sShaderProgram.c_str()));
	glBindVertexArray(m_iVAO);
	// TODO The mode should be configurable
	glDrawElements(GL_TRIANGLES, m_iIndicesCount, GL_UNSIGNED_INT, 0);
}
