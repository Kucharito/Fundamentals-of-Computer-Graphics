#include "Model.h"

Model::Model(const float* points, size_t size, int vertexCount) : ModelInterface(points, size, vertexCount)
{
	this->vertexCount = vertexCount;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

void Model::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}

