#include "data.h"

GLuint vertexbuffer;
GLuint colorbuffer;
GLuint elementbuffer;

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

void init_buffer()
{
        //GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


        //GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);


        //GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_data), g_element_data, GL_STATIC_DRAW);


}

void init_heightmap()
{

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


	//GLuint terrain_colorbuffer;
	glGenBuffers(1, &terrain_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * SIZEX * SIZEZ, heightmap_color_data, GL_STATIC_DRAW);

	//GLuint terrain_normalbuffer;
	glGenBuffers(1, &terrain_normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, terrain_normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * SIZEX * SIZEZ, heightmap_normal_data, GL_STATIC_DRAW);



	//GLuint terrain_elementbuffer;
	glGenBuffers(1, &terrain_elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain_elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(heightmap_element_data), heightmap_element_data, GL_STATIC_DRAW);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(SIZEX * SIZEZ);

}
