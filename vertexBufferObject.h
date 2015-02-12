#ifndef _VERTEX_BUFFER_OBJECT_H
#define _VERTEX_BUFFER_OBJECT_H

#include "common_header.h"


class VertexBufferObject
{
    public:
	VertexBufferObject();
	~VertexBufferObject();

	void init_buffer(const float *data, UINT size, UINT index);

	GLuint getID();
	void useShader();
	void addShader(GLuint shader);
	void setVAO(GLuint vao);
    private:
	vector<GLuint> _buffer;

	GLuint _shader;
};

#endif
