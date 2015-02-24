#include "scene.h"

Scene::Scene(){}
Scene::~Scene(){}

GLuint programID;
GLuint modelID;
GLuint viewID;
GLuint projectionID;

Shader2 brdfID2;
Shader2 lightShader;

Texture glassTex;
Texture grassTex;

ObjectFactory primitiveFactoryy;
Object suzunnaObj;
Object suzunnaObj2;
Object groundObj;

MaterialFactory materialFactory;
//ShaderProgram shader1;

DirectionalLight directionalLight;

extern float tip;


void Scene::init()
{
    /* bind ground normal + texture*/
    Material surfaceMaterial = materialFactory.createColorMaterial(Color::RED);
    groundObj = primitiveFactoryy.createSquareObj(10.0f,10.0f, &surfaceMaterial);

    /* bind suzunnan1*/
    suzunnaObj = primitiveFactoryy.createCustomizedObj("obj/suzanne.obj", &surfaceMaterial);
    /* end bind suzunnan1 */

    /* bind suzunna2*/
    /*
    glGenVertexArrays(1, &(suzunnaObj2.VAO));
    glBindVertexArray(suzunnaObj2.VAO);

    suzunnaObj2.addData3D(t_cube_vertexbuffer);
    suzunnaObj2.addData2D(t_cube_uvbuffer);
    suzunnaObj2.addData3D(t_cube_normalbuffer);

    glBindVertexArray(0);
    */
    /* end bind suzunnan2 */

    /* set up matrix*/
    //shader1.loadShaders("shader/light.vlsl", "shader/light.flsl");
    programID = LoadShaders( "shader/light.vlsl", "shader/light.flsl" );
    modelID = glGetUniformLocation(programID, "M");
    viewID = glGetUniformLocation(programID, "V");
    projectionID = glGetUniformLocation(programID, "P");
    /* end set up matrix*/

    /* set up matrix*/
    brdfID2.loadShaders("shader/brdf.vlsl", "shader/brdf.flsl" );
    /* end set up matrix*/

    /* set up texture glass*/
    glassTex.texture = load_image("textures/metalplate.jpg");
    glassTex.textureID = glGetUniformLocation(programID, "textureSampler");
    /* end set up texture*/

    /* set up texture grass*/
    grassTex.texture = load_image("textures/grass.jpg");
    grassTex.textureID = glGetUniformLocation(programID, "textureSampler");
    /* end set up texture*/

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
    glUseProgram(programID);
    
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

    //glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(trans_ground));
    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(groundObj.modelM));
    //glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(groundObj.modelM));

    groundObj.render();

    trans = glm::rotate(modelM, 45.0f, glm::vec3(2.0,-2.0, 0.0));
    glm::mat4 trans2 = transpose(trans);
    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(trans2));
    //glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(groundObj.modelM));
    groundObj.render();
    grassTex.unbindTexture();
    /*end draw ground*/

    glUseProgramObjectARB(0);


    /*draw another suzunnan*/
    /*
    brdfID2.useProgram();
    trans = glm::translate(modelM, glm::vec3(0.0,-2.0, 0.0));
    brdfID2.setUniform("M", &trans);
    brdfID2.setUniform("P", &projectionM);
    brdfID2.setUniform("V", &viewM);

    glassTex.bindTexture();
    suzunnaObj.render();
    glassTex.unbindTexture();

    brdfID2.unloadShader();
    */
    /*end draw another suzunnan*/

}


