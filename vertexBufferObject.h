#ifndef _VERTEX_BUFFER_OBJECT_H
#define _VERTEX_BUFFER_OBJECT_H

#include "common_header.h"

class Object 
{
    public:
	Object();
	~Object();
        GLuint VAO;
        GLuint VBO[MAX_VBO];
        GLuint programID;
	void addData2D(vector<glm::vec2> v2);
	void addData3D(vector<glm::vec3> v3);

	void render();
    private:
	UINT vbo_no;
	UINT vertex_size;
	
};


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
