#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <GL/glew.h>

#include <iostream>

#include <GLFW/glfw3.h> 
#define GLM_ENABLE_EXPERIMENTAL


#include <glm/vec3.hpp> 
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 
#include <glm/gtx/string_cast.hpp>

#include <SOIL.h>

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h> 

using namespace std;


struct Data {
	GLuint VAO = 0;
	int indicesCount = 0;
};

class ModelLoader
{
private:
	Data data;
	struct Vertex
	{
		float Position[3];
		float Normal[3];
		float Texture[2];
		float Tangent[3];
	};
	
public:
	ModelLoader();
	~ModelLoader();
	Data loadModel(const char* path);
};

