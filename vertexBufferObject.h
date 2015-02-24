#ifndef _VERTEX_BUFFER_OBJECT_H
#define _VERTEX_BUFFER_OBJECT_H

#include "common_header.h"
#include "shaderProgram.h"
#include "material.h"
#include "common/objloader.hpp"


class Object 
{
    friend class ObjectFactory;

    public:
	Object();
	~Object();

	void render();
	void translate(float x0, float y0, float z0);
	void rotate(float angle, float x0, float y0, float z0);
	void scale(float x0, float y0, float z0);

        GLuint VAO;
        GLuint VBO[MAX_VBO];


	glm::mat4 modelM;
    private:
	void addData2D(vector<glm::vec2> v2);
	void addData3D(vector<glm::vec3> v3);
	void setMaterial(Material *m);

	UINT vbo_no;
	UINT vertex_size;
	Material *material;
};

class ObjectFactory
{
    typedef vector<glm::vec3> Buffer3D;
    typedef vector<glm::vec2> Buffer2D;

    public:
	ObjectFactory(){}
	~ObjectFactory(){}

	//create 3d primitive
	Object& createSphereObj(float radius, Material *m);
	Object& createCubeObj(float l, float w, float r, Material *m);
	Object& createConeObj(float radius, float h, Material *m);
	Object& createCustomizedObj(const char* path, Material *m);
	//create 3d primitive
	Object& createSquareObj(float l, float w, Material *m);
	Object& createTriangleObj();
    private:
	Object* bind(Buffer3D &vb, Buffer2D &uvb, Buffer3D nb); 
	Object* createObj();

};

#endif
