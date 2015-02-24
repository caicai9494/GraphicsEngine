#include "color.h"

Color::Color(float x_, float y_, float z_)
{
    isSet = true;

    x = x_;
    y = y_;
    z = z_;
}

glm::vec3 Color::RED(1.0, 0.0, 0.0);
glm::vec3 Color::GREEN(0.0, 1.0, 0.0);
glm::vec3 Color::BLUE(0.0, 0.0, 1.0);

glm::vec3 Color::getColor()
{
    if(!isSet) return RED;

    return glm::vec3(x, y, z);
}

void Color::setColor(float x_, float y_, float z_)
{
    isSet = true;

    x = x_;
    y = y_;
    z = z_;
}
