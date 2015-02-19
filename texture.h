#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "common_header.h"

class Texture
{
    public:
	Texture();
	~Texture();
	GLuint texture;
	GLuint textureID;
	GLuint texture_offset;

	static GLuint texture_total;

	void bindTexture(); 
	void unbindTexture(); 
    private:
	Texture(const Texture &t) {}
	Texture& operator= (const Texture &t) { return *this; }
};

#endif
