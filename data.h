#ifndef _DATA_H
#define _DATA_H

#include "common_header.h"
#include "common/objloader.hpp"


extern GLuint vertexbuffer;
extern GLuint colorbuffer;
extern GLuint elementbuffer;

static const int SIZEX = 4;
static const int SIZEZ = 4;

static const int LENX = 90;
static const int LENZ = 90;

static glm::vec3 heightmap_vertex_data[SIZEX * SIZEZ];
static glm::vec3 heightmap_normal_data[SIZEX * SIZEZ];
static glm::vec3 heightmap_color_data[SIZEX * SIZEZ];

extern GLuint terrain_vertexbuffer;
extern GLuint terrain_colorbuffer;
extern GLuint terrain_normalbuffer;
extern GLuint terrain_elementbuffer;

void init_buffer(GLuint VAO);
void init_heightmap(GLuint VAO);

/* color cube */
extern const GLfloat cube_vertexbuffer[108];
extern const GLfloat cube_colorbuffer[108];
extern const GLfloat cube_normalbuffer[108];

/* texture cube with normal */
extern vector<glm::vec3> t_cube_vertexbuffer;
extern vector<glm::vec2> t_cube_uvbuffer;
extern vector<glm::vec3> t_cube_normalbuffer;

/* color triangle */
extern const GLfloat triangle_vertexbuffer[9];
extern const GLfloat triangle_colorbuffer[9];
//extern GLuint cube_elementbuffer;

#endif
