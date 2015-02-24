#include "material.h"


void Material::setMaterial(Color c)
{
    color = c;
}

Material* MaterialFactory::createMat()
{
    return new Material();
}

Material& MaterialFactory::createColorMaterial(Color c)
{
    Material *m = createMat();

    m->setMaterial(c);

    return *m;
}

Material& MaterialFactory::createColorMaterial(glm::vec3 c)
{
    Material *m = createMat();

    m->color.setColor(c.x, c.y, c.z);

    return *m;
}
