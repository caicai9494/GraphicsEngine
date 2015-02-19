/////////////////////////////////////////////////////////////////////////////
// geomtypes.h
//
// Author: Alex Kozlowski (kman@graphics.ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
// Cube:     Single indexed model class that creates a cube.
//
// Sphere:   SI model that generates a sphere
//
/////////////////////////////////////////////////////////////////////////////
#ifndef CSE167_MODEL_TYPES_H_
#define CSE167_MODEL_TYPES_H_

#include "geometry.h"

/////////////////////////////////////////////////////////////////////////////
// Model
//
class Cube : public Geometry
{
////////////////////////////////
// Constructors/Destructors
public:

    Cube(float x_side=1, float y_side=1, float z_side=1);

};

class Sphere : public Geometry
{
////////////////////////////////
// Constructors/Destructors
public:

    Sphere(int theta_slices=10, int phi_slices=10, float radius=1.0);

};


#endif // CSE167_MODEL_TYPES_H_

