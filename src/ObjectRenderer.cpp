#include <iostream>
#include "ObjectRenderer.hpp"
#include "glad/glad.h"
#include "shader.hpp"
#include "texture.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ObjectRenderer::ObjectRenderer() : m_transformMatrix( glm::mat4(1.0f)) {}

void ObjectRenderer::init() {
	glGenVertexArrays(1, &m_iVAO);
	glGenBuffers(1, &m_iVBO);
	glGenBuffers(1, &m_iEBO);
}

void ObjectRenderer::setVertices(float* vertices, unsigned int* indices, int verticesSize, int indicesSize) {
	m_iIndicesCount = indicesSize / (int) sizeof(unsigned int);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
	glBindVertexArray(m_iVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize , vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	// Vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered
	// VBO as the vertex attribute's bound vertex buffer object so afterwards we
	// can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally
	// modify this VAO, but this rarely happens. Modifying other VAOs requires a
	// call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
	// VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void ObjectRenderer::setShaderProgram(std::string shaderProgram) {
	m_sShaderProgram = shaderProgram;
}

void ObjectRenderer::setTexture(std::string texture) {
	m_sTexture = texture;
}

void ObjectRenderer::render() const {
	GLuint shaderProgram = shader_getProgram(m_sShaderProgram.c_str());
	GLuint texture = texture_get(m_sTexture.c_str());

	float timeValue = (float) glfwGetTime();

	int timeLocation = glGetUniformLocation(shaderProgram, "currentTime");
	int transformLocation = glGetUniformLocation(shaderProgram, "transform");

	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1f(timeLocation, timeValue);
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(m_transformMatrix));

	glBindVertexArray(m_iVAO);
	// TODO The mode should be configurable
	glDrawElements(GL_TRIANGLES, m_iIndicesCount, GL_UNSIGNED_INT, 0);
}
