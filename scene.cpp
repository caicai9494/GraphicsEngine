#include "scene.h"

Scene::Scene(){}
Scene::~Scene(){}

GLuint modelID;
GLuint viewID;
GLuint projectionID;

Object obj;
Object obj2;

void Scene::init()
{
    /* bind cube */
    glGenVertexArrays(1, &(obj.VAO));
    glBindVertexArray(obj.VAO);

    glGenBuffers(1, &(obj.VBO[0]));
    glBindBuffer(GL_ARRAY_BUFFER, obj.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertexbuffer), cube_vertexbuffer, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &(obj.VBO[1]));
    glBindBuffer(GL_ARRAY_BUFFER, obj.VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colorbuffer), cube_colorbuffer, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
    /* end bind cube */

    /* bind triangle */
    glGenVertexArrays(1, &(obj2.VAO));
    glBindVertexArray(obj2.VAO);

    glGenBuffers(1, &(obj2.VBO[0]));
    glBindBuffer(GL_ARRAY_BUFFER, obj2.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertexbuffer), triangle_vertexbuffer, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &(obj2.VBO[1]));
    glBindBuffer(GL_ARRAY_BUFFER, obj2.VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colorbuffer), triangle_colorbuffer, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
    /* end bind triangle */

    GLuint programID = LoadShaders( "shader/SimpleVertexShader.vertexshader", "shader/SimpleFragmentShader.fragmentshader" );
    modelID = glGetUniformLocation(programID, "M");
    viewID = glGetUniformLocation(programID, "V");
    projectionID = glGetUniformLocation(programID, "P");
    obj.programID = programID;
    
}

void Scene::render()
{
    glUseProgram(obj.programID);

    glm::mat4 modelM = glm::mat4(1.0f);
    glm::mat4 viewM = glm::lookAt(
	    vec3(4.0, 3.0,-3.0),
	    vec3(0.0, 0.0, 0.0),
	    vec3(0.0, 1.0, 0.0)
	    );
    glm::mat4 projectionM = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelM));
    glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(viewM));
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projectionM));

    /*draw cube*/
    glBindVertexArray(obj.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    /*end draw cube*/

    /*draw triangle*/
    glBindVertexArray(obj2.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    /*end draw triangle*/

}


