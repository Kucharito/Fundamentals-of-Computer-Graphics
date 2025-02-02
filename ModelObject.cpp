#include "ModelObject.h"

ModelObject::ModelObject(const char* path) : ModelInterface()
{
	Data modelData = loadModel(path);
	VAO = modelData.VAO;
	indicesCount = modelData.indicesCount;
}

ModelObject::~ModelObject()
{
	glDeleteVertexArrays(1, &VAO);

}

void ModelObject::draw()
{
	if (VAO == 0 || indicesCount == 0)
	{
		cout << "Error: Failed to initialize model" << std::endl;
		return;
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


