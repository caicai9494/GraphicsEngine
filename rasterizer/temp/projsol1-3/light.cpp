/////////////////////////////////////////////////////////////////////////////
// light.cpp
///////////////////////////////////// 
#include "light.h"

int Light::s_NumLights = 0;
bool Light::s_LightingEnabled = false;

/////////////////////////////////////////////////////////////////////////////
// Name:           Light Constructor
// Arguments:      none
// Returns:        none
// Side Effects:   Initializes the light, assigning it a light number
//                 and other default lighting parameters
/////////////////////////////////////////////////////////////////////////////
Light::Light ()
{
    LightNum = ++s_NumLights;
    SetPosition (Point3 (0, 0, 0));
    SetAmbientColor (Vector3 (.0f, .0f, .0f));
    SetDiffuseColor (Vector3 (1, 1, 1));
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Light Destructor
// Arguments:      none
// Returns:        none
// Side Effects:   Disables this light in OpenGL
/////////////////////////////////////////////////////////////////////////////
Light::~Light ()
{
    --LightNum;
}


/////////////////////////////////////////////////////////////////////////////
// Name:           Draw
// Arguments:      none
// Returns:        none
// Side Effects:   Submits the lighting information to OpenGL for this light
// Notes:          Call this function at the begnning of each frame. Remember,
//                 the light position is affected by the contents of the
//                 current Modelview Matrix
/////////////////////////////////////////////////////////////////////////////
void Light::Draw ()
{
    glEnable (GL_LIGHT0 + LightNum);
    GLfloat LightAmbient[] = { AmbientColor.x, AmbientColor.y, AmbientColor.z, 1.0f };
    GLfloat LightDiffuse[] = { DiffuseColor.x, DiffuseColor.y, DiffuseColor.z, 1.0f };
    GLfloat LightPosition[]= { Position.x, Position.y, Position.z, 1.0f };

    glLightfv (GL_LIGHT0 + LightNum, GL_AMBIENT,  LightAmbient);
    glLightfv (GL_LIGHT0 + LightNum, GL_DIFFUSE,  LightDiffuse);
    glLightfv (GL_LIGHT0 + LightNum, GL_POSITION, LightPosition);
}
