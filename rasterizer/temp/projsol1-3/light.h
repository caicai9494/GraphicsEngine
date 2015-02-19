/////////////////////////////////////////////////////////////////////////////
// light.h
//
// Author: Wojciech Jarosz (wjarosz@ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
// Light:    A simple OpenGL light.
//
///////////////////////////////////// 
// History: 2006-Fall: Created by Wojciech Jarosz for CSE167 Fall 2005
//          2006-Winter: Minor updates by Alex Kozlowski for CSE167 Winter 2006           
/////////////////////////////////////////////////////////////////////////////

#ifndef CSE167_LIGHT_H_
#define CSE167_LIGHT_H_

#include "core.h"
#include "vector.h"

/////////////////////////////////////////////////////////////////////////////
// Light
//
class Light
{
////////////////////////////////
// Constructors/Destructors
public:
    Light ();
    ~Light ();
////////////////////////////////
// Local Procedures
public:
    void SetPosition (const Point3 &p)  {Position = p;}
    void SetAmbientColor (Vector3 c)    {AmbientColor = c;}
    void SetDiffuseColor (Vector3 c)    {DiffuseColor = c;}
    void Draw();

    static void EnableLighting ()       {glEnable (GL_LIGHTING); s_LightingEnabled = true;}
    static void DisableLighting ()      {glDisable (GL_LIGHTING); s_LightingEnabled = false;}
    static bool LightingEnabled ()      {return s_LightingEnabled;}

    Point3  Position;
    Vector3 DiffuseColor;
    Vector3 AmbientColor;
////////////////////////////////
// Member Variables
private:
    // Static variables
    static int s_NumLights;
    static bool s_LightingEnabled;
    int LightNum;
};

#endif // CSE167_LIGHT_H_
