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
Texture grassTex;

Object suzunnaObj;
Object groundObj;

ShaderProgram shader1;

DirectionalLight directionalLight;

extern float tip;


void Scene::init()
{
    /* bind ground normal + texture*/
    glGenVertexArrays(1, &(groundObj.VAO));
    glBindVertexArray(groundObj.VAO);

    groundObj.addData3D(t_ground_vertexbuffer);
    groundObj.addData2D(t_ground_uvbuffer);
    groundObj.addData3D(t_ground_normalbuffer);

    glBindVertexArray(0);

    /* bind cube normal + texture*/
    glGenVertexArrays(1, &(suzunnaObj.VAO));
    glBindVertexArray(suzunnaObj.VAO);

    suzunnaObj.addData3D(t_cube_vertexbuffer);
    suzunnaObj.addData2D(t_cube_uvbuffer);
    suzunnaObj.addData3D(t_cube_normalbuffer);

    glBindVertexArray(0);
    /* end bind cube */

    /* set up matrix*/
    //shader1.loadShaders("shader/light.vlsl", "shader/light.flsl");
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

    /* set up texture glass*/
    glassTex.texture = load_image("textures/metalplate.jpg");
    glassTex.textureID = glGetUniformLocation(programID, "textureSampler");
    /* end set up texture*/

    /* set up texture grass*/
    grassTex.texture = load_image("textures/grass.jpg");
    grassTex.textureID = glGetUniformLocation(programID, "textureSampler");
    /* end set up texture*/

    suzunnaObj.programID = programID;

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
    glUseProgram(suzunnaObj.programID);
    
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

    /*draw suzunna*/
    glassTex.bindTexture();
    /*move upwards*/
    glm::mat4 trans = glm::translate(modelM, glm::vec3(5.0,-2.0, 0.0));
    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(trans));

    suzunnaObj.render();
    glassTex.unbindTexture();
    /*end draw suzunna*/

    /*draw ground*/
    grassTex.bindTexture();

    /*move upwards*/
    glm::mat4 trans_ground = glm::scale(modelM, glm::vec3(10.0f));
    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(trans_ground));

    groundObj.render();

    trans = glm::rotate(modelM, 45.0f, glm::vec3(2.0,-2.0, 0.0));
    glm::mat4 trans2 = transpose(trans);
    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(trans2));
    groundObj.render();
    grassTex.unbindTexture();
    /*end draw ground*/

    glUseProgramObjectARB(0);


    /*draw another suzunnan*/
    glUseProgram(brdfID);
    glUniformMatrix4fv(b_viewID, 1, GL_FALSE, glm::value_ptr(viewM));
    glUniformMatrix4fv(b_projectionID, 1, GL_FALSE, glm::value_ptr(projectionM));

    trans = glm::translate(modelM, glm::vec3(0.0,-2.0, 0.0));
    glUniformMatrix4fv(b_modelID, 1, GL_FALSE, glm::value_ptr(trans));

    glassTex.bindTexture();
    suzunnaObj.render();
    glassTex.unbindTexture();

    glUseProgramObjectARB(0);
    /*end draw another suzunnan*/

}


