/////////////////////////////////////////////////////////////////////////////
// geometry.h
//
// Author: Alex Kozlowski (kman@graphics.ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
// Geometry: Single indexed model class that stores geometry as an array of 
//           triangles, points, normals, and colors.
//
// Triangle: Stores Vertex, Normal, and Color information for a single
//           triangle.
//
/////////////////////////////////////  
// History: 2006-Winter: Written by Alex Kozlowski for CSE167 Winter 2006           
/////////////////////////////////////////////////////////////////////////////

#ifndef CSE167_MODEL_H_
#define CSE167_MODEL_H_

#include "vector.h"
#include "color.h"

/////////////////////////////////////////////////////////////////////////////
// Triangle
//
class Triangle
{
////////////////////////////////
// Constructors/Destructors
public:
    Triangle() {}

////////////////////////////////
// Local Procedures
public:
    // Set pointers to vertices
    void SetVertices(int p0, int p1, int p2) 
        {VertexIndices[0] = p0; VertexIndices[1] = p1; VertexIndices[2] = p2;}

    // Set pointers to normals
    void SetNormals(int n0, int n1, int n2)
        {NormalIndices[0] = n0; NormalIndices[1] = n1; NormalIndices[2] = n2;}

    // Set pointers to colors
    void SetColors(int c0, int c1, int c2)
        {ColorIndices[0] = c0; ColorIndices[1] = c1; ColorIndices[2] = c2;}

////////////////////////////////
// Member Variables
public:
    int   VertexIndices[3];    
    int   NormalIndices[3];    
    int   ColorIndices[3];     
};


/////////////////////////////////////////////////////////////////////////////
// Geometry
//
class Geometry
{
////////////////////////////////
// Constructors/Destructors
public:
    Geometry();
    Geometry(int numVerts, int numNormals, int numColors, int numTris);
    // Destructor
    ~Geometry();

////////////////////////////////
// Local Procedures
public:
    // Initialize all arrays with the appropriate sizes
    void Init(int numVerts, int numNormals, int numColors, int numTris);

    // Triangle Accessor function
    Triangle* GetTriangle(int i)
        { return &pTris[i]; } 

    int GetNumTriangles()
        { return numTriangles;}

    // Calculate the Bounding Sphere (Leave for Next Assignment)
    void CalcBoundingSphere( Point3 &boundingCenter, float &boundingRadius);

////////////////////////////////
// Member Variables
public:
    Point3    *pVertices;
    Vector3   *pNormals;
    Color3    *pColors;
    Triangle  *pTris;
    int       numTriangles;
    int       numVertices;
    int       numNormals;
    int       numColors;

};


#endif // CSE167_MODEL_H_
