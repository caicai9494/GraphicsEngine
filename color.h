#ifndef COLOR_H
#define COLOR_H

#include "common_header.h"

class Color
{
    public:
	Color(){}
	Color(float x_, float y_, float z_);
	~Color(){}

	static glm::vec3 RED;
	static glm::vec3 GREEN;
	static glm::vec3 BLUE;

	glm::vec3 getColor();
	void setColor(float x_, float y_, float z_);
    private:
	float x,y,z;
	bool isSet;
};

#endif
