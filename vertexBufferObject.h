#ifndef _VERTEX_BUFFER_OBJECT_H
#define _VERTEX_BUFFER_OBJECT_H

#include "common_header.h"
#include "shaderProgram.h"
#include "common/objloader.hpp"


class Object 
{
    public:
	Object();
	~Object();
        GLuint VAO;
        GLuint VBO[MAX_VBO];

	void addData2D(vector<glm::vec2> v2);
	void addData3D(vector<glm::vec3> v3);

	void render();

	//ShaderProgram shader;

    private:
	UINT vbo_no;
	UINT vertex_size;
	
};

class ObjectFactory
{
    public:
	ObjectFactory(){}
	~ObjectFactory(){}

	//create 3d primitive
	Object& createSphereObj();
	Object& createCubeObj();
	Object& createConeObj();
	Object& createCustomizedObj(const char* path);
	//create 3d primitive
	Object& createSquareObj(float w, float h);
	Object& createTriangleObj(float w, float h);
    private:
};

/*
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

*/
#endif
