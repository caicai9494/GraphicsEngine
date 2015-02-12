#include "light.h"

DirectionalLight::DirectionalLight(){}
DirectionalLight::~DirectionalLight(){}

void DirectionalLight::setDirection(glm::vec3 v)
{
    direction = v;
}

void DirectionalLight::setColor(glm::vec3 v)
{
    color = v;
}
void DirectionalLight::setAmbientIntensity(float v)
{
    fAmbientIntensity = v;
}

glm::vec3 DirectionalLight::getDirection()
{
    return direction;
}
glm::vec3 DirectionalLight::getColor()
{
    return color;
}
float* DirectionalLight::getAmbientIntensity()
{
    return &fAmbientIntensity;
}
