#include "texture.h"

Texture::Texture()
{
    texture_total ++;
    texture_offset = texture_total;
}
Texture::~Texture(){}

GLuint Texture::texture_total = -1;

void Texture::bindTexture()
{

    glActiveTexture(GL_TEXTURE0 + texture_offset);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, texture_offset);
}

void Texture::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
