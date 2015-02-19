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
	static GLuint texture_offset;

	void bindTexture(GLenum text = GL_TEXTURE0); 
	void unbindTexture(); 
    private:
	Texture(const Texture &t) {}
	Texture& operator= (const Texture &t) { return *this; }
};

#endif
