////////////////////////////////////////////////////////////////////////////////
// geomtypes.cpp
///////////////////////////////////// 

#include "geomtypes.h"


/////////////////////////////////////////////////////////////////////////////
// Name:           Cube constructor
// Arguments:      Lengths for x, y, and z sides. Cube is centered at (0,0,0)
//                 x_side, y_side, and z_side all have default values of 1
// Returns:        none
// Side Effects:   Initializes the cube of 12 triangles with sides of length
//                 as stated above. No colors are specified
//
/////////////////////////////////////////////////////////////////////////////
Cube::Cube(float x_side, float y_side, float z_side) 
{
	// 8 Vertices, 6 Normals, no colors, 12 Triangles
	Init(8,6,0,12);
	float x = x_side *0.5f;
	float y = y_side *0.5f;
	float z = z_side *0.5f;

	pVertices[0].Set( x,-y, z);
    pVertices[1].Set( x,-y,-z);
    pVertices[2].Set( x, y,-z);
    pVertices[3].Set( x, y, z);
    pVertices[4].Set(-x,-y, z);
    pVertices[5].Set(-x,-y,-z);
    pVertices[6].Set(-x, y,-z);
    pVertices[7].Set(-x, y, z);

	pNormals[0].Set( 1,0,0);
	pNormals[1].Set(-1,0,0);
	pNormals[2].Set(0, 1,0);
	pNormals[3].Set(0,-1,0);
	pNormals[4].Set(0,0, 1);
	pNormals[5].Set(0,0,-1);

	// Right Side Vertices
	pTris[0].SetVertices(0,1,2);
	pTris[1].SetVertices(0,2,3);
	// Right Side Normals
	pTris[0].SetNormals(0,0,0);
	pTris[1].SetNormals(0,0,0);

	// Left Side Vertices
	pTris[2].SetVertices(4,6,5);
	pTris[3].SetVertices(4,7,6);
	// Left Side Normals
	pTris[2].SetNormals(1,1,1);
	pTris[3].SetNormals(1,1,1);

	// Bottom Side Vertices
	pTris[4].SetVertices(1,0,4);
	pTris[5].SetVertices(1,4,5);
	// Bottom Side Normals
	pTris[4].SetNormals(3,3,3);
	pTris[5].SetNormals(3,3,3);

	// Rear Side Vertices
	pTris[6].SetVertices(2,1,5);
	pTris[7].SetVertices(2,5,6);
	// Rear Side Normals
	pTris[6].SetNormals( 5, 5, 5);
	pTris[7].SetNormals( 5, 5, 5);
 
	// Top Side Vertices
	pTris[8].SetVertices(3,2,6);
	pTris[9].SetVertices(3,6,7);
	// Top Side Normals
	pTris[8].SetNormals( 2, 2, 2);
	pTris[9].SetNormals( 2, 2, 2);
 
	// Front Side Vertices
	pTris[10].SetVertices(0,3,7);
	pTris[11].SetVertices(0,7,4);
	// Front Side Normals
	pTris[10].SetNormals( 4, 4, 4);
	pTris[11].SetNormals( 4, 4, 4);

}

//***************************************************************************
//**************** Do not alter anything above this line *********************
//************************** Begin Assignment *********************************

/////////////////////////////////////////////////////////////////////////////
// Name:           Sphere constructor
// Arguments:      Number of slices in both theta and phi, as well as a radius
// Returns:        none
// Side Effects:   Initializes the sphere with the above parameters. No colors 
//                 are specified
/////////////////////////////////////////////////////////////////////////////
Sphere::Sphere(int theta_slices, int phi_slices, float radius){

	// TODO: Implement Sphere Tesselation
	
}

//************************** End Assignment *********************************
//**************** Do not alter anything past this line *********************
//***************************************************************************
