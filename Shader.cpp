#include "Shader.h"

Shader::Shader(const char* shaderSource, GLenum shaderType)
{
	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);
}

GLuint Shader::getShaderID()
{
	return shaderID;
}
