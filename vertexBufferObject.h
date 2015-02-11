#ifndef _VERTEX_BUFFER_OBJECT_H
#define _VERTEX_BUFFER_OBJECT_H

#include "common_header.h"

class VertexBufferObject
{
    public:
	void init_buffer(void *data, UINT datasize);
    private:
	GLuint buffer;
};

#endif
