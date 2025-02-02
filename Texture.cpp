#include "Texture.h"
#include <SOIL.h>
#include <iostream>


Texture::Texture(const char* path, int textureUnit)
{
	this->textureUnit = textureUnit;
	glActiveTexture(GL_TEXTURE0 + textureUnit);

	textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (textureID == 0)
	{
		std::cout << "An error occurred while loading image. " <<path<< std::endl;
		exit(EXIT_FAILURE);
	}
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	unbind();
}

Texture::Texture(const char* posx, const char* negx, const char* posy, const char* negy, const char* posz, const char* negz, int textureUnit)
{
	this->textureUnit = textureUnit;
	glActiveTexture(GL_TEXTURE0 + textureUnit);

	textureID = SOIL_load_OGL_cubemap(posx, negx, posy, negy, posz, negz, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (textureID == 0)
	{
		std::cout << "An error occurred while loading image." << std::endl;
		exit(EXIT_FAILURE);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	unbind();
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureID() const
{
	return textureID;
}

int Texture::getTextureUnit() const
{
	return textureUnit;
}
