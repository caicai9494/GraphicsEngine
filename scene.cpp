#include "scene.h"

Scene::Scene(){}
Scene::~Scene(){}

GLuint modelID;
GLuint viewID;
GLuint projectionID;

GLuint brdfID;
GLuint b_modelID;
GLuint b_viewID;
GLuint b_projectionID;

//GLuint Texture;
//GLuint TextureID;
Texture glassTex;



Object obj;
Object obj2;

DirectionalLight directionalLight;

extern float tip;


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
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &(obj.VBO[2]));
    glBindBuffer(GL_ARRAY_BUFFER, obj.VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, t_cube_normalbuffer.size() * sizeof(glm::vec3), &t_cube_normalbuffer[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
    /* end bind cube */

    /* set up matrix*/
    GLuint programID = LoadShaders( "shader/light.vlsl", "shader/light.flsl" );
    modelID = glGetUniformLocation(programID, "M");
    viewID = glGetUniformLocation(programID, "V");
    projectionID = glGetUniformLocation(programID, "P");
    /* end set up matrix*/

    /* set up matrix*/
    brdfID = LoadShaders( "shader/brdf.vlsl", "shader/brdf.flsl" );
    b_modelID = glGetUniformLocation(programID, "M");
    b_viewID = glGetUniformLocation(programID, "V");
    b_projectionID = glGetUniformLocation(programID, "P");
    /* end set up matrix*/

    /* set up texture*/
    //Texture = loadDDS("textures/uvtemplate.DDS");
    glassTex.texture = load_image("textures/metalplate.jpg");
    glassTex.textureID = glGetUniformLocation(programID, "textureSampler");
    /* end set up texture*/

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
    glUniform3fv(directionalLight.colorID, 1, glm::value_ptr(directionalLight.getColor()));
    glUniform1fv(directionalLight.ambientID, 1, directionalLight.getAmbientIntensity());

    /*draw cube*/
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, glassTex.texture);
    glUniform1i(glassTex.textureID, 0);

    glBindVertexArray(obj.VAO);
    glDrawArrays(GL_TRIANGLES, 0, t_cube_vertexbuffer.size());
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    /*end draw cube*/

    glUseProgramObjectARB(0);


    /*draw another suzunnan*/
    glUseProgram(brdfID);
    glUniformMatrix4fv(b_viewID, 1, GL_FALSE, glm::value_ptr(viewM));
    glUniformMatrix4fv(b_projectionID, 1, GL_FALSE, glm::value_ptr(projectionM));

    glm::mat4 trans = glm::translate(modelM, glm::vec3(2.0, 1.0, 0.0));
    glUniformMatrix4fv(b_modelID, 1, GL_FALSE, glm::value_ptr(trans));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, glassTex.texture);
    glUniform1i(glassTex.textureID, 0);

    glBindVertexArray(obj.VAO);
    glDrawArrays(GL_TRIANGLES, 0, t_cube_vertexbuffer.size());
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgramObjectARB(0);
    /*end draw another suzunnan*/

}


