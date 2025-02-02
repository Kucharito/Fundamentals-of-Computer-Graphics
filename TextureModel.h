#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <GL/glew.h>
#include <string>
#include "Model.h"
#include "Texture.h"

class TextureModel : public ModelInterface {
public:
	TextureModel(const float* points, size_t size, int vertexCount);
	~TextureModel();
	void draw();

};