#include "vertexBufferObject.h"

VertexBufferObject::VertexBufferObject()
{
    //glGenVertexArrays(1, &_vao);
    //glBindVertexArray(_vao);
}

VertexBufferObject::~VertexBufferObject()
{
}

void VertexBufferObject::init_buffer(const float *data, UINT size, UINT index) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);

    //glEnableVertexAttribArray(index);
    //glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    _buffer.push_back(buffer);
}

void VertexBufferObject::useShader()
{
    glUseProgram(_shader);
}
GLuint VertexBufferObject::getID()
{
    return _shader;
}
void VertexBufferObject::addShader(GLuint shader)
{
    _shader = shader;
}



