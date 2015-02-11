#include "common_header.h"

GLFWwindow* window;

const int WINDOW_HEIGHT = 768;
const int WINDOW_WIDTH = 1024;
const float WINDOW_RATIO = (float)WINDOW_WIDTH / WINDOW_HEIGHT;
const char* WINDOW_TITLE = "Graphics Test";

// Include GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include "common/shader.hpp"
#include "data.h"

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	//GLuint VertexArrayID, terrainVAO;
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	//glGenVertexArrays(1, &terrainVAO);
	glBindVertexArray(VertexArrayID);
	glBindVertexArray(0);
	
	//glBindVertexArray(terrainVAO);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "shader/SimpleVertexShader.vertexshader", "shader/SimpleFragmentShader.fragmentshader" );
	GLuint projectionMatrixID = glGetUniformLocation(programID, "P");
	GLuint viewMatrixID = glGetUniformLocation(programID, "M");
	GLuint modelMatrixID = glGetUniformLocation(programID, "V");
	GLuint normalID = glGetUniformLocation(programID, "N");
	GLuint lightDirectionID = glGetUniformLocation(programID, "sunlight.lightDirection");
	GLuint lightColorID = glGetUniformLocation(programID, "sunlight.lightColor");
	GLuint lightAmbientID = glGetUniformLocation(programID, "sunlight.fAmbientIntensity");
	glm::mat4 Projection = glm::perspective(45.0f, WINDOW_RATIO, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(
		    glm::vec3(0,80,30),
		    glm::vec3(0,0,0),
		    glm::vec3(0,1,0)
		);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	init_buffer();
	init_heightmap();

	double lastTime = glfwGetTime();
	do{

	        //count FPS
		static int frame = 0;

		double currentTime = glfwGetTime();
		if(currentTime - lastTime >= 1)
		{
		    printf("FPS %d per second\n", frame);
		    frame = 0;
		    lastTime++;
		}
		else
		    frame++;

		//simple animation
		static float tip;
		const float step = 0.050;
		const float begin = 0.000;
		const float end = 359.000;

		tip += step;
		if(tip > end) tip = begin;


	        glm::mat4 currentM;
	        glm::mat4 currentV;
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);
		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(Projection));

		//currentV = glm::rotate(View, tip, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(View));
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(Model));

		//Normal
		glm::mat4 normalMatrix = glm::mat4(1.0f);
		glUniformMatrix4fv(normalID, 1, GL_FALSE, glm::value_ptr(normalMatrix));
		//Light
		glm::vec3 lightDirection = glm::vec3(3,4,3);
		glUniform3fv(lightDirectionID, 1, glm::value_ptr(lightDirection));

		glm::vec3 lightColor = glm::vec3(1,0,0);
		glUniform3fv(lightColorID, 1, glm::value_ptr(lightColor));

		GLfloat ambient = 0.5f;
		glUniform1fv(lightAmbientID, 1, &ambient);

	        glBindVertexArray(VertexArrayID);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		//
		//glDrawArrays(GL_TRIANGLES, 0, 12); // 3 indices starting at 0 -> 1 triangle
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		/*
		glDrawElements(

			GL_TRIANGLES,
			12          ,
			GL_UNSIGNED_INT,
			(void*)0

		);
		*/

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, terrain_vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, terrain_colorbuffer);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, terrain_normalbuffer);
		glVertexAttribPointer(
			2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		//
		//glDrawArrays(GL_TRIANGLES, 0, 12); // 3 indices starting at 0 -> 1 triangle
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain_elementbuffer);
		glDrawElements(

			GL_TRIANGLE_STRIP,
			18,
			GL_UNSIGNED_INT,
			(void*)0

		);


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

