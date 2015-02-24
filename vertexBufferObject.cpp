#include "vertexBufferObject.h"

Object::Object()
{
    vbo_no = 0;
    vertex_size = 0;

    modelM = glm::mat4(1.0f);
    material = NULL;
}

Object::~Object()
{
    for(UINT i = 0; i < vbo_no; i++)
	glDeleteBuffers(1, &VBO[i]);

    glDeleteVertexArrays(1, &VAO);
}

void Object::setMaterial(Material *m)
{
    material = m;
}
void Object::translate(float x0, float y0, float z0)
{
    glm::vec3 v = glm::vec3(x0, y0, z0);
    modelM = glm::translate(modelM, v);
}
void Object::rotate(float angle, float x0, float y0, float z0)
{
    glm::vec3 v = glm::vec3(x0, y0, z0);
    modelM = glm::rotate(modelM, angle, v);
}
void Object::scale(float x0, float y0, float z0)
{
    glm::vec3 v = glm::vec3(x0, y0, z0);
    modelM = glm::scale(modelM, v);
}

Object* ObjectFactory::createObj()
{
    return new Object();
}
Object* ObjectFactory::bind(Buffer3D &vb, Buffer2D &uvb, Buffer3D nb)
{
    Object *obj;
    obj= createObj();

    glGenVertexArrays(1, &(obj->VAO));
    glBindVertexArray(obj->VAO);

    obj->addData3D(vb);
    obj->addData2D(uvb);
    obj->addData3D(nb);

    glBindVertexArray(0);

    return obj;
}
Object& ObjectFactory::createCustomizedObj(const char* path, Material *m)
{
    Buffer3D vertexbuffer;
    Buffer2D uvbuffer;
    Buffer3D normalbuffer;

    bool res = loadOBJ(path, vertexbuffer, uvbuffer, normalbuffer);

    assert(res);

    Object *obj;
    obj = bind(vertexbuffer, uvbuffer, normalbuffer);

    return *obj;
}
Object& ObjectFactory::createSquareObj(float l, float w, Material *m)
{

    glm::vec3 _t_ground_vertexbuffer[] = {
	//right upper
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(-1.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, -1.0f),

	//left lower
	glm::vec3(-1.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, -1.0f),
	glm::vec3(-1.0f, 0.0f, -1.0f),
    };
    Buffer3D vertexbuffer(_t_ground_vertexbuffer, _t_ground_vertexbuffer + sizeof(_t_ground_vertexbuffer) / sizeof(glm::vec3));;
    glm::vec2 _t_ground_uvbuffer[] = {
	//right upper
	glm::vec2(1.0f, 1.0f),
	glm::vec2(-1.0f, 1.0f),
	glm::vec2(1.0f, -1.0f),

	//left lower
	glm::vec2(-1.0f, 1.0f),
	glm::vec2(1.0f, -1.0f),
	glm::vec2(-1.0f, -1.0f),
    };
    Buffer2D uvbuffer(_t_ground_uvbuffer, _t_ground_uvbuffer + sizeof(_t_ground_uvbuffer) / sizeof(glm::vec2));;
    glm::vec3 _t_ground_normalbuffer[] = {
	//right upper
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
    };
    Buffer3D normalbuffer(_t_ground_normalbuffer, _t_ground_normalbuffer + sizeof(_t_ground_normalbuffer) / sizeof(glm::vec3));;


    Object *obj;
    obj = bind(vertexbuffer, uvbuffer, normalbuffer);
    obj->scale(l,1,w);

    return *obj;
}

void Object::addData2D(vector<glm::vec2> v2)
{
    if(!vertex_size)
	vertex_size = v2.size();
    else
	assert(v2.size() == vertex_size);

    assert(vbo_no < MAX_VBO);

    glGenBuffers(1, &(VBO[vbo_no]));
    glBindBuffer(GL_ARRAY_BUFFER, VBO[vbo_no]);
    glBufferData(GL_ARRAY_BUFFER, v2.size() * sizeof(glm::vec2), &v2[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(vbo_no);
    glVertexAttribPointer(vbo_no, sizeof(glm::vec2) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, 0, (void*)0);

    vbo_no++;
}

void Object::addData3D(vector<glm::vec3> v3)
{
    
    if(!vertex_size)
	vertex_size = v3.size();
    else
	assert(v3.size() == vertex_size);

    assert(vbo_no < MAX_VBO);

    glGenBuffers(1, &(VBO[vbo_no]));
    glBindBuffer(GL_ARRAY_BUFFER, VBO[vbo_no]);
    glBufferData(GL_ARRAY_BUFFER, v3.size() * sizeof(glm::vec3), &v3[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(vbo_no);
    glVertexAttribPointer(vbo_no, sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, 0, (void*)0);

    vbo_no++;
}

void Object::render()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_size);
    glBindVertexArray(0);
}
