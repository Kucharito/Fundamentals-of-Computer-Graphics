#pragma once

// Author: Adam Kuch�r
// Login: KUC0396

#include <GL/glew.h>
#include <stdlib.h>

class ModelInterface {
protected:
	GLuint VAO;
	GLuint VBO;
	int vertexCount;
public:
	ModelInterface();
	ModelInterface(const float* points, size_t size, int vertexCount);
	virtual void draw()=0;	
};