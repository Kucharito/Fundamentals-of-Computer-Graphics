#pragma once

// Author: Adam Kuch�r
// Login: KUC0396

#include <GL/glew.h>
#include <stdlib.h>
#include "ModelInterface.h"

class Model : public ModelInterface
{
protected:
	/*GLuint VAO;
	GLuint VBO;
	int vertexCount;
	*/
public:
	Model(const float* points,size_t size, int vertexCount);
	void draw();
};

