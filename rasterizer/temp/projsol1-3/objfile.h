/////////////////////////////////////////////////////////////////////////////
// modeltypes.h
//
// Author: Alex Kozlowski (kman@graphics.ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
// Cube:     Single indexed model class that creates a cube.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef CSE167_OBJFILE_H_
#define CSE167_OBJFILE_H_

#include "geometry.h"
#include "matrix.h"

////////////////////////////////
// Constructors/Destructors
class ObjFile : public Geometry
{

public:
	ObjFile(char* fileName,Matrix &M);
};

#endif // CSE167_OBJFILE_H_

