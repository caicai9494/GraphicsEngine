#include "data.h"



const GLfloat triangle_vertexbuffer[9] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
};

const GLfloat triangle_colorbuffer[9] = { 
		 1.0f,  0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
		 0.0f,  0.0f, 1.0f,
};

const GLfloat cube_vertexbuffer[108] = { 
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};

	// One color for each vertex. They were generated randomly.
const GLfloat cube_colorbuffer[108] = { 
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
};
GLuint vertexbuffer;
GLuint colorbuffer;
GLuint elementbuffer;
GLuint normalbuffer;

GLuint terrain_vertexbuffer;
GLuint terrain_colorbuffer;
GLuint terrain_normalbuffer;
GLuint terrain_elementbuffer;

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
	    0, 3, 1,
	    0, 4, 3,
	    0, 4, 2,
};

static const GLfloat g_color_buffer_data[] = { 
	         //front
		 0.0f,  1.0f, 0.0f,
		 1.0f,  0.0f, 1.0f,
		 1.0f,  0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
};

static float fheights[SIZEX * SIZEZ] = {
	    4.0f, 2.0f, 13.0f, 1.0f,
	    3.0f, 5.0f, 8.0f, 2.0f,
	    7.0f, 10.0f, 2.0f, 6.0f,
	    4.0f, 6.0f, 8.0f, 3.0f
};

static int heightmap_element_data[] = {
	    0,4,1,5,2,6,3,7,16,
	    4,8,5,9,6,10,7,11,16,
	    8,12,9,13,10,14,11,15
};

void init_buffer(GLuint VAO)
{
        int inx1, inx2, inx3;
        glm::vec3 normal_buffer[4];

	for(int i = 0; i < 4; i++)
	{
	    inx1 = g_element_data[3*i];
	    inx2 = g_element_data[3*i + 1];
	    inx3 = g_element_data[3*i + 2];

	    glm::vec3 v1 = vec3(g_vertex_buffer_data[3*inx1+1], 
		                g_vertex_buffer_data[3*inx1+1],
				g_vertex_buffer_data[3*inx1+2]);
	    glm::vec3 v2 = vec3(g_vertex_buffer_data[3*inx2], 
		                g_vertex_buffer_data[3*inx2+1],
				g_vertex_buffer_data[3*inx2+2]);
	    glm::vec3 v3 = vec3(g_vertex_buffer_data[3*inx3], 
		                g_vertex_buffer_data[3*inx3+1],
				g_vertex_buffer_data[3*inx3+2]);
	    normal_buffer[i] = glm::cross(v1-v2, v1-v3);
	}

        glBindVertexArray(VAO);
        //GLuint vertexbuffer;
	// 1rst attribute buffer : vertices
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);


        //GLuint colorbuffer;
	// 1rst attribute buffer : color
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

        //GLuint normalbuffer;
	// 1rst attribute buffer : normal
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normal_buffer), normal_buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

        //GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_data), g_element_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);


}

void init_heightmap(GLuint VAO)
{
        glBindVertexArray(VAO);

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

	//GLuint terrain_vertexbuffer;
	glGenBuffers(1, &terrain_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * SIZEX * SIZEZ, heightmap_vertex_data, GL_STATIC_DRAW);
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


	//GLuint terrain_colorbuffer;
	glGenBuffers(1, &terrain_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * SIZEX * SIZEZ, heightmap_color_data, GL_STATIC_DRAW);
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

	//GLuint terrain_normalbuffer;
	glGenBuffers(1, &terrain_normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * SIZEX * SIZEZ, heightmap_normal_data, GL_STATIC_DRAW);
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



	//GLuint terrain_elementbuffer;
	glGenBuffers(1, &terrain_elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain_elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(heightmap_element_data), heightmap_element_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}
