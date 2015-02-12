#include "scene.h"

Scene::Scene(){}
Scene::~Scene(){}

VertexBufferObject vbo;
GLuint vao[1];

void Scene::init()
{
    glGenVertexArrays(1, &vao[0]);
    glBindVertexArray(vao[0]);

    vbo.init_buffer(cube_vertexbuffer, 108, 0);
    //vbo.init_buffer(cube_colorbuffer, 108, 1);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindVertexArray(0);



    GLuint programID = LoadShaders( "shader/SimpleVertexShader.vertexshader", "shader/SimpleFragmentShader.fragmentshader" );
    vbo.addShader(programID);
    
}

void Scene::render()
{
    glBindVertexArray(vao[0]);
    vbo.useShader();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


