/////////////////////////////////////////////////////////////////////////////
// matrix.h
//
// Author: Alex Kozlowski (kman@graphics.ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
// Matrix: 
//
// Layout: Column Notation
//
//         M = | m_m[0]  m_m[4]  m_m[8]   m_m[12] |
//             | m_m[1]  m_m[5]  m_m[9]   m_m[13] | 
//             | m_m[2]  m_m[6]  m_m[10]  m_m[14] |
//             | m_m[3]  m_m[7]  m_m[11]  m_m[15] |
//
// For notational purposes, we use column major format, which implies we post-
// multiply our matrices (see examples below).  However, OpenGL reqires that 
// our matrices lie in rows in memory.  We will stick to the column convention 
// throughout CSE167. 
//
// The Matrix class implements the implicit float*() operator and can be 
// passed directly to OpenGL.
//
///////////////////////////////////// 
// Common Operations Supported:
//
// Matrix ma, mb, mc;    // Matrices
// Vector3  v, w;        // Vectors
// Point3   p, q         // Points
//
// v = ma * w;           // Matrix-Vector Multiply  v = ma * w
// ma.Transform(w,v);    // Matrix-Vector Multiply  v = ma * w
// p = ma * q;           // Matrix-Point Multiply   p = ma * q
// ma.Transform(q,p);    // Matrix-Point Multiply   p = ma * q
// ma = mb * mc;         // Matrix-Matrix Multiply  ma = mb * mc
// ma.Multiply(mb, mc);  // Matrix-Matrix Multiply  ma = mb * mc
//
// 
///////////////////////////////////// 
// History: 2004-Winter: Created by Steve Rotenberg for CSE169 Winter 2004
//          2006-Winter: Heavily modified by Alex Kozlowski for CSE167 Winter 2006           
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

#ifndef CSE167_MATRIX_H_
#define CSE167_MATRIX_H_

#include "vector.h"


/////////////////////////////////////////////////////////////////////////////
// Matrix
//
class Matrix {

////////////////////////////////
// Constructors/Destructors
//
public:
    Matrix() {Identity();}
    Matrix(float m0, float m4, float m8,  float m12,  // First Row
           float m1, float m5, float m9,  float m13,  // Second Row
           float m2, float m6, float m10, float m14,  // Third Row
           float m3, float m7, float m11, float m15); // Fourth Row
    Matrix(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Point3 &d);

////////////////////////////////
// Local Procedures
//  
    // '_m' must be ordered by columns, such that the first four entries in '_m'
    // correspond to the first column in 'm_m'
    void Set(const float *_m)                       {memcpy(m_m,_m,16*sizeof(float));} 

    void Set(float m0, float m4, float m8,  float m12,  // First Row
             float m1, float m5, float m9,  float m13,  // Second Row
             float m2, float m6, float m10, float m14,  // Third Row
             float m3, float m7, float m11, float m15); // Fourth Row
    void Set(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Point3 &d);

    void Identity();

    // Multiply : this = 'm (dot) n' 
    void Multiply(const Matrix &m, const Matrix &n);

    // Optimized Transform for affine Transformations (post-multiplying)
    void Transform(const Vector3 &in,Vector3 &out) const;
    void Transform(const Point3  &in,Point3  &out) const;
    
    // Accessors
    void GetA(Vector3 &out);
    void GetB(Vector3 &out);
    void GetC(Vector3 &out);
    void GetD(Point3  &out);

    // Modifiers
    void SetA(float ax, float ay, float az);    
    void SetB(float bx, float by, float bz);
    void SetC(float cx, float cy, float cz);
    void SetD(float dx, float dy, float dz);


    // MakeRotate (NOTE: t is an angle in RADIANS)
    void MakeRotateX(float t);
    void MakeRotateY(float t);
    void MakeRotateZ(float t);
    void MakeRotateUnitAxis(const Vector3 &v,float t);  // v must be normalized

    // Scale
    void MakeScale(float x,float y,float z);
    void MakeScale(const Vector3 &v)                {MakeScale(v.x,v.y,v.z);}
    void MakeScale(float s)                         {MakeScale(s,s,s);}

    // Translate
    void MakeTranslate(float x,float y,float z);
    void MakeTranslate(const Vector3 &v)            {MakeTranslate(v.x, v.y,v.z);}
    void Translate(const Vector3 &v);

    // Full 16 pt Matrix Transform (post-multiplying)
    void TransformFull(const Point3 &in, Point3 &out) const;

    void Transpose();
    void Print(const char *s=0) const;
////////////////////////////////
// Overloaded Operators
//
public:
    operator float*()                               {return &m_m[0];}

    //***********************************IMPORTANT***********************************\\ 
    // The following operators use the OPTIMIZED versions of the Transform function, 
    Vector3 operator*(const Vector3 &v) const       {Vector3 out; Transform(v,out); return out;}
    Point3  operator*(const Point3  &p) const       {Point3  out; Transform(p,out); return out;}
    Matrix  operator*(const Matrix &m) const        {Matrix n; n.Multiply(*this,m); return n;}

////////////////////////////////
// Overloaded Operators
//
public:
    // Static matrices
    static Matrix IDENTITY;

public:
    float m_m[16];
};

#endif
