#ifndef _SCENE_H
#define _SCENE_H

#include "common_header.h"
#include "data.h"
#include "vertexBufferObject.h"
#include "light.h"
#include "common/shader.hpp"
#include "common/controls.hpp"
#include "common/objloader.hpp"
#include "common/texture.hpp"

class Scene
{
    public:
	Scene();
	~Scene();
	void init();
	void render();
    private:
	Scene(const Scene &s) {}
	Scene& operator= (const Scene& s) { return *this;}
};

#endif
