// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
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

#define SHADER_DIR  "shader/"
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

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "shader/SimpleVertexShader.vertexshader", "shader/SimpleFragmentShader.fragmentshader" );
	GLuint projectionMatrixID = glGetUniformLocation(programID, "P");
	GLuint viewMatrixID = glGetUniformLocation(programID, "M");
	GLuint modelMatrixID = glGetUniformLocation(programID, "V");
	glm::mat4 Projection = glm::perspective(45.0f, WINDOW_RATIO, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(
		    glm::vec3(0,15,60),
		    glm::vec3(0,0,0),
		    glm::vec3(0,1,0)
		);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;



	static const GLfloat g_vertex_buffer_data[] = { 
	         //front
		 0.0f,  5.0f, 0.0f,
		-5.0f,  0.0f, 3.0f,
		 5.0f,  0.0f, 3.0f,

	         //left
		 0.0f,  5.0f, 0.0f,
		-5.0f,  0.0f,-3.0f,
		-5.0f,  0.0f, 3.0f,

	         //right
		 0.0f,  5.0f, 0.0f,
		 5.0f,  0.0f, 3.0f,
		 5.0f,  0.0f,-3.0f,

	         //back
		 0.0f,  5.0f, 0.0f,
		-5.0f,  0.0f,-3.0f,
		 5.0f,  0.0f,-3.0f,

		 /*
		 //botton left
		-5.0f,  0.0f,-3.0f,
		 5.0f,  0.0f, 3.0f,
		-5.0f,  0.0f, 3.0f,

		 //botton right
		 5.0f,  0.0f, 3.0f,
		-5.0f,  0.0f, 3.0f,
		 5.0f,  0.0f,-3.0f,
		 */
	};

	static const GLfloat g_color_buffer_data[] = { 
	         //front
		 0.0f,  1.0f, 0.0f,
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 0.0f,

	         //left
		 0.0f,  1.0f, 0.0f,
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 1.0f,

	         //right
		 0.0f,  1.0f, 0.0f,
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 1.0f,

	         //back
		 0.0f,  1.0f, 0.0f,
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 1.0f,

		 /*
		 //botton left
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 1.0f,

		 //botton right
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 1.0f,
		 */
	};

	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	do{

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
		//glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(Projection));

		currentV = glm::rotate(View, tip, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(currentV));
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(Model));

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
		glDrawArrays(GL_TRIANGLES, 0, 12); // 3 indices starting at 0 -> 1 triangle

		//currentM = glm::translate(Model, glm::vec3(-20.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(currentM));
		//glDrawArrays(GL_TRIANGLES, 0, 12); // 3 indices starting at 0 -> 1 triangle

		currentM = glm::rotate(Model, tip, glm::vec3(0.0f, 0.0f, 1.0f));
		currentM = glm::translate(currentM, glm::vec3(10.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(currentM));
		glDrawArrays(GL_TRIANGLES, 0, 12); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

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

