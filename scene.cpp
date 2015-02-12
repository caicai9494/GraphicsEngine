#include "scene.h"

Scene::Scene(){}
Scene::~Scene(){}

GLuint modelID;
GLuint viewID;
GLuint projectionID;

Object obj;
Object obj2;

DirectionalLight directionalLight;


void Scene::init()
{
    /* bind cube normal + texture*/
    glGenVertexArrays(1, &(obj.VAO));
    glBindVertexArray(obj.VAO);

    glGenBuffers(1, &(obj.VBO[0]));
    glBindBuffer(GL_ARRAY_BUFFER, obj.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, t_cube_vertexbuffer.size() * sizeof(glm::vec3), &t_cube_vertexbuffer[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &(obj.VBO[1]));
    glBindBuffer(GL_ARRAY_BUFFER, obj.VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, t_cube_uvbuffer.size() * sizeof(glm::vec2), &t_cube_uvbuffer[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &(obj.VBO[2]));
    glBindBuffer(GL_ARRAY_BUFFER, obj.VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, t_cube_normalbuffer.size() * sizeof(glm::vec3), &t_cube_normalbuffer[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

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


    GLuint programID = LoadShaders( "shader/light.vlsl", "shader/light.flsl" );
    modelID = glGetUniformLocation(programID, "M");
    viewID = glGetUniformLocation(programID, "V");
    projectionID = glGetUniformLocation(programID, "P");
    obj.programID = programID;

    /*set directional light*/
    directionalLight.setDirection(glm::vec3(0.0, -1.0, 0.0));
    directionalLight.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    directionalLight.setAmbientIntensity(0.5f);
    directionalLight.directionID = glGetUniformLocation(programID, "sunlight.direction");
    directionalLight.colorID = glGetUniformLocation(programID, "sunlight.color");
    directionalLight.ambientID = glGetUniformLocation(programID, "sunlight.ambient");
    /*end set directional light*/
    
}

void Scene::render()
{
    glUseProgram(obj.programID);
    computeMatricesFromInputs();

    /*set MVP */
    glm::mat4 modelM = glm::mat4(1.0f);
    glm::mat4 viewM = getViewMatrix();
    glm::mat4 projectionM = getProjectionMatrix();

    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelM));
    glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(viewM));
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projectionM));
    /*end set MVP */

    glUniform3fv(directionalLight.directionID, 1, glm::value_ptr(directionalLight.getDirection()));
    //glUniform3fv(directionalLight.directionID, 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
    glUniform3fv(directionalLight.colorID, 1, glm::value_ptr(directionalLight.getColor()));
    glUniform1fv(directionalLight.ambientID, 1, directionalLight.getAmbientIntensity());

    /*draw cube*/
    glBindVertexArray(obj.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    /*end draw cube*/

    /*draw triangle*/
    glBindVertexArray(obj2.VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    /*end draw triangle*/

}


