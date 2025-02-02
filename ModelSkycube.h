#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <GL/glew.h>
#include <string>
#include "Model.h"
class ModelSkycube : public ModelInterface{
private:

public:
	ModelSkycube(const float *points, size_t size, int vertexCount);
	~ModelSkycube();
	void draw();


};