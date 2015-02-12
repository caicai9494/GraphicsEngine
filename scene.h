#ifndef _SCENE_H
#define _SCENE_H

#include "common_header.h"
#include "data.h"
#include "vertexBufferObject.h"
#include "common/shader.hpp"

class Scene
{
    public:
	Scene();
	~Scene();
	void init();
	void render();
};

#endif
