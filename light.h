#ifndef _LIGHT_H
#define _LIGHT_H
#include "common_header.h"

class DirectionalLight
{
    public:
	DirectionalLight();
	~DirectionalLight();

	void setDirection(glm::vec3 v);
	void setColor(glm::vec3 v);
	void setAmbientIntensity(float v);

	glm::vec3 getDirection();
	glm::vec3 getColor();
	float* getAmbientIntensity();

	GLuint directionID;
	GLuint colorID;
	GLuint ambientID;

    private:
	glm::vec3 direction;
	glm::vec3 color; 

	float fAmbientIntensity;

	DirectionalLight(const DirectionalLight& d) {}
	DirectionalLight& operator= (const DirectionalLight &d) { return *this; }
};

#endif
