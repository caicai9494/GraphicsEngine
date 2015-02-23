#ifndef MATERIAL_H
#define MATERIAL_H

#include "common_header.h"

class Material
{
    public:
	Material(Color c)
	{ 
	    color = c;
	}
	virtual ~Material(){}
    private:
	Color color;
};

#endif
