#include "ModelSkycube.h"

ModelSkycube::ModelSkycube(const float* points, size_t size, int vertexCount) : ModelInterface(points, size, vertexCount)
{
	this->vertexCount = vertexCount;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
}

ModelSkycube::~ModelSkycube()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void ModelSkycube::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}
