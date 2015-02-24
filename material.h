#ifndef MATERIAL_H
#define MATERIAL_H

#include "common_header.h"

class Material
{
    friend class MaterialFactory;
    public:
	Material(){}
	virtual ~Material(){}

    private:
	void setMaterial(Color c);
	Color color;
};

class MaterialFactory
{
    public:
	MaterialFactory(){}
	~MaterialFactory(){}

	Material& createColorMaterial(Color c);
	Material& createColorMaterial(glm::vec3 c);
    private:
	Material* createMat();
};


#endif
