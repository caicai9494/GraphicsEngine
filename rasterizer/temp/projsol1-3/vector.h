/////////////////////////////////////////////////////////////////////////////
// vector.h
//
// Author: Alex Kozlowski (kman@graphics.ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
//
// Vector3: A vector class representing vectors in 3 dimensions (x,y,z).
//
//
// Point3:  A point class representing points in 3 dimensions (x,y,z)
//          Points differ from vectors in that points represent locations in 
//          space, rather than directions. As a result, the two support 
//          different operations.
//
// Point3 and Vector3 classes implement the implicit float*() operator and
// can be passed directly to OpenGL.
//
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
//
///////////////////////////////////// 
// History: 2004-Winter: Created by Steve Rotenberg for CSE169 Winter 2004
//          2006-Winter: Modified by Alex Kozlowski for CSE167 Winter 2006
/////////////////////////////////////////////////////////////////////////////

#ifndef CSE167_VECTOR_H_
#define CSE167_VECTOR_H_

#include "core.h"

////////////////////////////////
// Forward Declarations
//
class Vector3;
class Point3;

/////////////////////////////////////////////////////////////////////////////
// Vector3
//
class Vector3 {

////////////////////////////////
// Constructors/Destructors
//
public:
    Vector3()                                           {x=0.0f; y=0.0f; z=0.0f;}
    Vector3(float x0,float y0,float z0)                 {x=x0; y=y0; z=z0;}

////////////////////////////////
// Local Procedures
//
public:
    void Set(Vector3 &v)                                {x=v.x; y=v.y; z=v.z;}
    void Set(float x0,float y0,float z0)                {x=x0; y=y0; z=z0;}
    void Zero()                                         {x=y=z=0.0f;}

    // Algebra
    void Add(const Vector3 a)                           {x+=a.x; y+=a.y; z+=a.z;}
    void Add(const Vector3 a,const Vector3 b)           {x=a.x+b.x; y=a.y+b.y; z=a.z+b.z;}
    void Subtract(const Vector3 a)                      {x-=a.x; y-=a.y; z-=a.z;}
    void Subtract(const Vector3 a,const Vector3 b)      {x=a.x-b.x; y=a.y-b.y; z=a.z-b.z;}

    void Scale(float s)                                 {x*=s; y*=s; z*=s;}
    void Scale(const Vector3 a,float s)                 {x=a.x*s; y=a.y*s; z=a.z*s;}
    
    // returns the result of 'this (dot) a'
    float Dot(const Vector3 a) const;
    // Sets 'this' equal to 'a (cross) b' 
    void Cross(const Vector3 a,const Vector3 b);

    // Normalizes the vector (Mag==1)
    void Normalize();
    void Negate()                                       {x=-x; y=-y; z=-z;}

    // Magnitude of the vector (length)
    float Mag() const;
    // Magnitude squared of the vector
    float MagSq() const;

    // Misc functions
    void Print(char *name=0) const                      {if(name) printf("%s=",name); printf("{%f,%f,%f}\n",x,y,z);}

////////////////////////////////
// Overloaded Operators
//
public:
    operator float*()                                   {return (float*)this;}
    float &operator[](int i)                            {return(((float*)this)[i]);}
    Vector3 &operator+=(const Vector3 &v)               {x+=v.x; y+=v.y; z+=v.z; return *this;}
    Vector3 &operator-=(const Vector3 &v)               {x-=v.x; y-=v.y; z-=v.z; return *this;}
    Vector3 &operator*=(float f)                        {x*=f; y*=f; z*=f; return *this;}

////////////////////////////////
// Member Variables
//
public:
    // Static vectors
    static Vector3 XAXIS,YAXIS,ZAXIS;
    static Vector3 ORIGIN;
public:
    float x,y,z;
};



/////////////////////////////////////////////////////////////////////////////
// Point3
//
class Point3 {

////////////////////////////////
// Constructors/Destructors
//
public:
    Point3()                                            {x=0.0f; y=0.0f; z=0.0f;}
    Point3(float x0,float y0,float z0)                  {x=x0; y=y0; z=z0;}
    explicit Point3(const Vector3 &v)                   {x=v.x; y=v.y; z=v.z;}

////////////////////////////////
// Local Procedures
//
public:
    void Set(Point3 &p)                                 {x=p.x; y=p.y; z=p.z;}
    void Set(float x0,float y0,float z0)                {x=x0; y=y0; z=z0;}
    void Zero()                                         {x=y=z=0.0f;}

    // Algebra
    void Add(const Vector3 a)                           {x+=a.x; y+=a.y; z+=a.z;}
    void Add(const Point3 a,const Vector3 b)            {x=a.x+b.x; y=a.y+b.y; z=a.z+b.z;}
    void Subtract(const Vector3 a)                      {x-=a.x; y-=a.y; z-=a.z;}
    void Subtract(const Point3 a,const Vector3 b)       {x=a.x-b.x; y=a.y-b.y; z=a.z-b.z;}
    void Scale(float s)                                 {x*=s; y*=s; z*=s;}
    void Scale(const Point3 a,float s)                  {x=a.x*s; y=a.y*s; z=a.z*s;}
    void Negate()                                       {x=-x; y=-y; z=-z;}

    // Returns the distance between two points
    float Dist(const Point3 a) const                    {return sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y)+(z-a.z)*(z-a.z));}
    // Returns the distance squared between two points
    float DistSq(const Point3 a) const                  {return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y)+(z-a.z)*(z-a.z);}
    // Linearly interpolate between two points
    void Lerp(float t,const Point3 a,const Point3 b)    {Scale(a,1.0f-t); x+=b.x*t; y+=b.y*t; z+=b.z*t;}

    // Misc functions
    void Print(char *name=0) const                      {if(name) printf("%s=",name); printf("{%f,%f,%f}\n",x,y,z);}

	// For convenience when we need to treat a Point as a Vector
	Vector3 ToVector3()	const							{return Vector3(x,y,z);}

////////////////////////////////
// Overloaded Operators
//
public:
    float &operator[](int i)                            {return(((float*)this)[i]);}
    Point3 &operator+=(const Vector3 &v)                {x+=v.x; y+=v.y; z+=v.z; return *this;}
    Point3 &operator-=(const Vector3 &v)                {x-=v.x; y-=v.y; z-=v.z; return *this;}
    Point3 &operator*=(float f)                         {x*=f; y*=f; z*=f; return *this;}

    operator float*()                                   {return (float*)this;}

////////////////////////////////
// Member Variables
//
public:
    float x,y,z;
};



/////////////////////////////////////////////////////////////////////////////
// External Inline Operators
//

 inline Vector3 operator-(const Vector3 &v);
 inline Vector3 operator+(const Vector3 &v, const Vector3 &w);
 inline Vector3 operator-(const Vector3 &v, const Vector3 &w);
 inline Vector3 operator*(float f, const Vector3 &w);
 inline Vector3 operator*(const Vector3 &w, float f);
 inline Vector3 operator/(const Vector3 &v, float f);
 inline Vector3 operator/(float f, const Vector3 &v);

 inline Point3  operator-(const Point3 &p);
 inline Point3  operator+(const Point3 &p, const Vector3 &w);
 inline Point3  operator-(const Point3 &p, const Vector3 &w);
 inline Vector3 operator-(const Point3 &p, const Point3 &q);
 inline Point3  operator*(float f, const Point3 &p);
 inline Point3  operator*(const Point3 &p, float f);

/////////////////////////////////////////////////////////////////////////////
// External Operator Implementations
//

inline Vector3 operator-(const Vector3 &v)
{
  return Vector3(-v.x, -v.y, -v.z);
}

inline Vector3 operator-(const Vector3 &v, const Vector3 &w)
{
  return Vector3(v.x - w.x, v.y - w.y, v.z - w.z);
}

inline Vector3 operator+(const Vector3 &v, const Vector3 &w)
{
  return Vector3(v.x + w.x, v.y + w.y, v.z + w.z);
}

inline Vector3 operator*(float f, const Vector3 &v)
{
  return Vector3(v.x*f, v.y*f, v.z*f);
}
inline Vector3 operator*(const Vector3 &v, float f)
{
  return Vector3(v.x*f, v.y*f, v.z*f);
}

inline Vector3 operator/(const Vector3 &v, float f)
{
  f = 1./f;
  return Vector3(v.x*f, v.y*f, v.z*f);
}

inline Vector3 operator/(float f, const Vector3 &v)
{
  return Vector3(f/v.x, f/v.y, f/v.z);
}

inline Point3  operator-(const Point3 &p) 
{
  return Point3(-p.x, -p.y, -p.z);
}
inline Point3  operator+(const Point3 &p, const Vector3 &w) 
{
  return Point3(p.x + w.x, p.y + w.y, p.z + w.z);
}

inline Point3  operator-(const Point3 &p, const Vector3 &w) 
{
  return Point3(p.x - w.x, p.y - w.y, p.z - w.z);
}

inline Vector3  operator-(const Point3 &p, const Point3 &q)
{
  return Vector3(p.x - q.x, p.y - q.y, p.z - q.z);
}

inline Point3  operator*(float f, const Point3 &p)
{
  return Point3(p.x*f, p.y*f, p.z*f);
}

inline Point3  operator*(const Point3 &p, float f)
{
  return Point3(p.x*f, p.y*f, p.z*f);
}

#endif
