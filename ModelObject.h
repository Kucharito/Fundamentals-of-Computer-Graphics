#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "ModelLoader.h"
#include "ModelInterface.h"

class ModelObject : public ModelLoader, public ModelInterface
{
private:
	int indicesCount;
public:
	ModelObject(const char* path);
	~ModelObject();

	void draw();


};

