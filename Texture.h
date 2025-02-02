#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <GL/glew.h>
#include <string>
class Texture {
private:
	GLuint textureID;
	int textureUnit;


public:
	Texture(const char* path, int textureUnit);
	Texture(const char* posx, const char* negx, const char* posy, const char* negy, const char* posz, const char* negz, int textureUnit);
	~Texture();
	void bind() const;
	void unbind() const;

	GLuint getTextureID() const;
	int getTextureUnit() const;

};
