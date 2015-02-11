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

	GLuint VertexArrayID, terrainVAO;
	glGenVertexArrays(1, &VertexArrayID);
	glGenVertexArrays(1, &terrainVAO);
	glBindVertexArray(VertexArrayID);
	glBindVertexArray(terrainVAO);

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



	static const GLfloat g_vertex_buffer_data[] = { 
	         //top
		 0.0f,  5.0f, 0.0f,
		 //left front
		-5.0f,  0.0f, 3.0f,
		 //left back
		-5.0f,  0.0f,-3.0f,
		 //right front
		 5.0f,  0.0f, 3.0f,
		 //right back
		 5.0f,  0.0f,-3.0f,

	};

	static const GLuint g_element_data[] = { 
	    0, 1, 2,
	    0, 1, 3,
	    0, 3, 4,
	    0, 2, 4,
	};

	static const GLfloat g_color_buffer_data[] = { 
	         //front
		 0.0f,  1.0f, 0.0f,
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
	};

	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_data), g_element_data, GL_STATIC_DRAW);

	const int SIZEX = 4;
	const int SIZEZ = 4;
	glm::vec3 heightmap_vertex_data[SIZEX * SIZEZ];
	glm::vec3 heightmap_normal_data[SIZEX * SIZEZ];
	glm::vec3 heightmap_color_data[SIZEX * SIZEZ];

	static float fheights[SIZEX * SIZEZ] = {
	    4.0f, 2.0f, 13.0f, 1.0f,
	    3.0f, 5.0f, 8.0f, 2.0f,
	    7.0f, 10.0f, 2.0f, 6.0f,
	    4.0f, 6.0f, 8.0f, 3.0f
	};

	const int LENX = 90;
	const int LENZ = 90;
	for(int i = 0; i < SIZEX * SIZEZ; i++)
	{
	    float x,z;

	    z = (float)i / SIZEZ;
	    x = float(i % SIZEX);

	    heightmap_vertex_data[i] = 
		glm::vec3(
		        -LENX/2 + x * LENX / float(SIZEX - 1),
			fheights[i],
			-LENZ/2 + z * LENZ / float(SIZEZ - 1)
			);
	    heightmap_color_data[i] = 
		glm::vec3(
			(float)i/10, (float)i/4, (float)(SIZEX * SIZEZ - i)/11
			);
	}

	static int heightmap_element_data[] = {
	    0,4,1,5,2,6,3,7,16,
	    4,8,5,9,6,10,7,11,16,
	    8,12,9,13,10,14,11,15
	};

	for(int i = 0; i < SIZEX * SIZEZ; i++)
	{
	    static int inx = 0;
	    if(inx != SIZEX * SIZEZ - 1 && !inx && inx % (SIZEX + 1) == 0)
		inx += 4;
		
	    int i1 = heightmap_element_data[inx];
	    int i2 = heightmap_element_data[inx+1];
	    int i3 = heightmap_element_data[inx+2];
	    inx++;

	    /*
	    if(i1 > SIZEX * SIZEZ - 1 || i2 > SIZEX * SIZEZ -1 || i3 > SIZEX * SIZEZ -1)
	    {
		i--;
		continue;
	    }
	    */

	    glm::vec3 v1 = heightmap_vertex_data[i1];
	    glm::vec3 v2 = heightmap_vertex_data[i2];
	    glm::vec3 v3 = heightmap_vertex_data[i3];

	    if(i % 2 == 0) heightmap_normal_data[i] = glm::cross(v1 - v2, v1 - v3);
	    else heightmap_normal_data[i] = -glm::cross(v1 - v2, v1 - v3);

	}

	GLuint terrain_vertexbuffer;
	glGenBuffers(1, &terrain_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * SIZEX * SIZEZ, heightmap_vertex_data, GL_STATIC_DRAW);

	GLuint terrain_colorbuffer;
	glGenBuffers(1, &terrain_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * SIZEX * SIZEZ, heightmap_color_data, GL_STATIC_DRAW);

	GLuint terrain_normalbuffer;
	glGenBuffers(1, &terrain_normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * SIZEX * SIZEZ, heightmap_normal_data, GL_STATIC_DRAW);

	GLuint terrain_elementbuffer;
	glGenBuffers(1, &terrain_elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain_elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(heightmap_element_data), heightmap_element_data, GL_STATIC_DRAW);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(SIZEX * SIZEZ);

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

