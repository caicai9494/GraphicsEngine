////////////////////////////////////////////////////////////////////////////////
// vector3.cpp
///////////////////////////////////// 
// Common Operations Supported:
//
// Vector3  u, v, w; // Vectors
// Point3   p, q     // Points
// FLOAT f;          // Scalar
//
// f = v[0];       // LHS Index Operation
// v[0] = f;       // LHS Index Operation
// f = p[0];       // LHS Index Operation
// p[0] = f;       // LHS Index Operation
//
// u = v;
// u = -v;         // Vector Negation
// u += v;         // Vector Addition
// u = v + w;      // Vector Addition
// u -= v;         // Vector Subtraction
// u = v - w;      // Vector Subtraction
// u *= f;         // Scalar Multiplication
// u = v * f;      // Scalar Multiplication
// u = f * v;      // Scalar Multiplication
// u = v / f;      // Scalar Division
// u = f / v;      // Scalar Inversion
// u.Cross(v,w);   // Cross product u = v (cross) w
// f = v.Dot(w);   // Dot Product f = v (dot) w
//
// p = q;
// p = -q;         // Point Negation
// p += v;         // Point Vector Addition
// p = q + v;      // Point Vector Addition
// p -= v;         // Point Vector Subtraction
// p = q - v;      // Point Vector Subtraction
// p *= f;         // Point Scalar Multiplication
// p = v * f;      // Scalar Multiplication
// p = f * v;      // Scalar Multiplication
////////////////////////////////////////////////////////////////////////////////

#include "vector.h"

////////////////////////////////////////////////////////////////////////////////
// Static members

Vector3 Vector3::XAXIS(1.0f,0.0f,0.0f);
Vector3 Vector3::YAXIS(0.0f,1.0f,0.0f);
Vector3 Vector3::ZAXIS(0.0f,0.0f,1.0f);
Vector3 Vector3::ORIGIN(0.0f,0.0f,0.0f);



//***************************************************************************
//**************** Do not alter anything above this line ********************
//************************* Begin Assignment ********************************




/////////////////////////////////////////////////////////////////////////////
// Name:           Dot
// Arguments:      A vector
// Returns:        the result of this (dot) a
// Side Effects:   None               
/////////////////////////////////////////////////////////////////////////////
float Vector3::Dot(const Vector3 a) const
{
    return x*a.x + y*a.y + z*a.z;
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Cross
// Arguments:      Two vectors to cross (Order matters)
// Returns:        none
// Side Effects:   Sets this vector to the result of a (cross) b              
/////////////////////////////////////////////////////////////////////////////
void Vector3::Cross(const Vector3 a,const Vector3 b)    
{
    x = a.y*b.z - a.z*b.y;
    y = a.z*b.x - a.x*b.z;
    z = a.x*b.y - a.y*b.x;
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Normalize
// Arguments:      none
// Returns:        none
// Side Effects:   Normalizes this vector              
/////////////////////////////////////////////////////////////////////////////
void Vector3::Normalize()
{
    float mag = Mag();
    
    x /= mag;
    y /= mag;
    z /= mag;
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Mag
// Arguments:      none
// Returns:        The magnitude of this vector
/////////////////////////////////////////////////////////////////////////////
float Vector3::Mag() const
{
    return sqrt(MagSq());
}

/////////////////////////////////////////////////////////////////////////////
// Name:           MagSq
// Arguments:      none
// Returns:        The magnitude squared of this vector
/////////////////////////////////////////////////////////////////////////////
float Vector3::MagSq() const
{
    return x*x + y*y + z*z;
}

//************************** End Assignment *********************************
//**************** Do not alter anything past this line *********************
//***************************************************************************
