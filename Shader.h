#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Shader
{
private:
	GLuint shaderID;

public:
	Shader(const char* shaderSource, GLenum shaderType);
	GLuint getShaderID();

};

