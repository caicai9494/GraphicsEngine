#include "texture.h"

Texture::Texture()
{
    texture_offset ++;
}
Texture::~Texture(){}

GLuint Texture::texture_offset = -1;

void Texture::bindTexture(GLenum text)
{

    glActiveTexture(text + texture_offset);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, texture_offset);
}

void Texture::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
