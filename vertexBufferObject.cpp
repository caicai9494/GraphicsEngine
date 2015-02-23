#include "vertexBufferObject.h"

Object::Object()
{
    vbo_no = 0;
    vertex_size = 0;
}

Object::~Object()
{
    for(UINT i = 0; i < vbo_no; i++)
	glDeleteBuffers(1, &VBO[i]);

    glDeleteVertexArrays(1, &VAO);
}

Object& ObjectFactory::createCustomizedObj(const char* path)
{
    vector<glm::vec3> vertexbuffer;
    vector<glm::vec2> uvbuffer;
    vector<glm::vec3> normalbuffer;

    bool res = loadOBJ(path, vertexbuffer, uvbuffer, normalbuffer);

    assert(res);

    Object *obj = new Object();

    glGenVertexArrays(1, &(obj->VAO));
    glBindVertexArray(obj->VAO);

    obj->addData3D(vertexbuffer);
    obj->addData2D(uvbuffer);
    obj->addData3D(normalbuffer);

    glBindVertexArray(0);

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

/*
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



*/
