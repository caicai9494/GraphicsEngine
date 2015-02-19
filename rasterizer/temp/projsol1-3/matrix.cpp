/////////////////////////////////////////////////////////////////////////////
// matrix.cpp
////////////////////////////////////////
// Layout: Column Notation
//
//         M = | m_m[0]  m_m[4]  m_m[8]   m_m[12] |
//             | m_m[1]  m_m[5]  m_m[9]   m_m[13] | 
//             | m_m[2]  m_m[6]  m_m[10]  m_m[14] |
//             | m_m[3]  m_m[7]  m_m[11]  m_m[15] |
//
// For notational purposes, we use column major format, which implies we post-
// multiply our matrices (see examples below).  However, OpenGL reqires that 
// our matrices lie in rows in memory.  
//
///////////////////////////////////// 
// Commmon Operations Supported:
//
// Matrix ma, mb, mc;    // Matrices
// Vector3  v, w;        // Vectors
// Point3   p, q         // Points
//
// v = ma * w;           // Vector Dot Product v = ma (dot) w
// ma.Transform(w,v);    // Vector Dot Product v = ma (dot) w
// p = ma * q;           // Point  Dot Product p = ma (dot) q
// ma.Transform(q,p);    // Point  Dot Product p = ma (dot) q
// ma = mb * mc;         // Matrix Multiply    ma = mb (dot) mc
// ma.Multiply(mb, mc);  // Matrix Multiply    ma = mb (dot) mc
//
// 
/////////////////////////////////////////////////////////////////////////////


#include "matrix.h"

Matrix Matrix::IDENTITY(1.0f,0.0f,0.0f,0.0f,
                        0.0f,1.0f,0.0f,0.0f,
                        0.0f,0.0f,1.0f,0.0f,
                        0.0f,0.0f,0.0f,1.0f);

/////////////////////////////////////////////////////////////////////////////
// Name:           Matrix constructor
// Arguments:      16 float values
// Returns:        none
// Side Effects:   Sets this matrix to the provided 16 values  
// Notes:          For convenience the 16 entries are provided in row order.
/////////////////////////////////////////////////////////////////////////////
Matrix::Matrix(float m0, float m4, float m8,  float m12,  // First Row
               float m1, float m5, float m9,  float m13,  // Second Row
               float m2, float m6, float m10, float m14,  // Third Row
               float m3, float m7, float m11, float m15)  // Fourth Row
{
    Set(m0,m4,m8, m12,
        m1,m5,m9, m13,
        m2,m6,m10,m14,
        m3,m7,m11,m15);
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Matrix constructor
// Arguments:      A,B,C Vectors and D Point representing 3 coordinate axis 
//                 and position
// Returns:        none
// Side Effects:   Sets this matrix values appropriately
//                 Last row is set to 0,0,0,1
/////////////////////////////////////////////////////////////////////////////
Matrix::Matrix(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Point3 &d) 
{

    Set(a,b,c,d);
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Set
// Arguments:      16 float values
// Returns:        none
// Side Effects:   Sets this matrix to the provided 16 values               
// Notes:          For convenience the 16 entries are provided in row order,
//                 which differs form other Set methods
/////////////////////////////////////////////////////////////////////////////
void Matrix::Set(float m0, float m4, float m8,  float m12,  // First Row
                 float m1, float m5, float m9,  float m13,  // Second Row
                 float m2, float m6, float m10, float m14,  // Third Row
                 float m3, float m7, float m11, float m15)  // Fourth Row
{
    m_m[0] = m0; m_m[4] = m4; m_m[8] = m8;   m_m[12] = m12; 
    m_m[1] = m1; m_m[5] = m5; m_m[9] = m9;   m_m[13] = m13; 
    m_m[2] = m2; m_m[6] = m6; m_m[10] = m10; m_m[14] = m14; 
    m_m[3] = m3; m_m[7] = m7; m_m[11] = m11; m_m[15] = m15; 

}

/////////////////////////////////////////////////////////////////////////////
// Name:           Identity
// Arguments:      none
// Returns:        none
// Side Effects:   Sets this matrix to the identity matrix.
/////////////////////////////////////////////////////////////////////////////
void Matrix::Identity() {
	*this = IDENTITY;
}

//***************************************************************************
//**************** Do not alter anything above this line ********************
//************************* Begin Assignment ********************************




/////////////////////////////////////////////////////////////////////////////
// Name:           Set
// Arguments:      A,B,C Vectors and D Point representing 3 coordinate axis 
//                 and position
// Returns:        none
// Side Effects:   Sets this matrix values appropriately
//                 Last row is set to 0,0,0,1
/////////////////////////////////////////////////////////////////////////////
void Matrix::Set(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Point3 &d) {

    m_m[0] = a.x; m_m[4] = b.x; m_m[8] = c.x;  m_m[12] = d.x; 
    m_m[1] = a.y; m_m[5] = b.y; m_m[9] = c.y;  m_m[13] = d.y; 
    m_m[2] = a.z; m_m[6] = b.z; m_m[10] = c.z; m_m[14] = d.z; 
    m_m[3] = 0;   m_m[7] = 0;   m_m[11] = 0;   m_m[15] = 1; 

}


/////////////////////////////////////////////////////////////////////////////
// Name:           Multiply
// Arguments:      Matrix m and Matrix n
// Returns:        none
// Side Effects:   Sets this matrix to the result of m (dot) n
// **IMPORTANT**:  Should work properly if this is equal to either m or n
/////////////////////////////////////////////////////////////////////////////
void Matrix::Multiply(const Matrix &m,const Matrix &n) {

    float _m[16];

    for(int i = 0; i < 4; i++) {

        for(int j = 0; j < 4; j++) {
			int i4 = i*4;
            _m[i4+j] = 0; 
            for(int k = 0; k < 4; k++) {    
                _m[i4+j] += m.m_m[k*4+j] * n.m_m[i4+k];
            }
        }
    }

    Set(&_m[0]);
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Transform
// Arguments:      The point to be transformed (in) and the point to store 
//                 the result (out). 
// Returns:        none
// Side Effects:   'out' is set to the result.
// Notes:          Optimized Transform for Rigid Body Transformations using
//                 post-multiplication for points.  Last row in the matrix is
//                 ignored.  
// **IMPORTANT**:  Should work properly if 'out' and 'in' are the same point.
/////////////////////////////////////////////////////////////////////////////
void Matrix::Transform(const Point3 &in,Point3 &out) const {
    float x=in.x*m_m[0] + in.y*m_m[4] + in.z*m_m[8] + m_m[12];
    float y=in.x*m_m[1] + in.y*m_m[5] + in.z*m_m[9] + m_m[13];
    float z=in.x*m_m[2] + in.y*m_m[6] + in.z*m_m[10] + m_m[14];
    out.Set(x,y,z);
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Transform
// Arguments:      The vector to be transformed (in) and the vector to store 
//                 the result (out). 
// Returns:        none
// Side Effects:   'out' is set to the result.
// Notes:          Optimized Transform for Rigid Body Transformations using
//                 post-multiplication for vectors.  Last row in the matrix is
//                 ignored.  
// **IMPORTANT**:  Should work properly if 'out' and 'in' are the same vector.
/////////////////////////////////////////////////////////////////////////////
void Matrix::Transform(const Vector3 &in,Vector3 &out) const {
    float x=in.x*m_m[0] + in.y*m_m[4] + in.z*m_m[8];
    float y=in.x*m_m[1] + in.y*m_m[5] + in.z*m_m[9];
    float z=in.x*m_m[2] + in.y*m_m[6] + in.z*m_m[10];
    out.Set(x,y,z);
}

/////////////////////////////////////////////////////////////////////////////
// Name:           TransformFull
// Arguments:      The point to be transformed (in) and the point to store 
//                 the result (out). 
// Returns:        none
// Side Effects:   'out' is set to the result (Homogenized).
// Notes:          Full 16 point matrix transform using post-multiplication 
//                 for points.  Automatically homogenize 'out' before 
//                 exiting, The 'w' component of 'in' is assumed to be 1. 
// **IMPORTANT**:  Should work properly if 'out' and 'in' are the same point.
/////////////////////////////////////////////////////////////////////////////
void Matrix::TransformFull(const Point3 &in, Point3 &out) const {
    float x=in.x*m_m[0] + in.y*m_m[4] + in.z*m_m[8] + m_m[12];
    float y=in.x*m_m[1] + in.y*m_m[5] + in.z*m_m[9] + m_m[13];
    float z=in.x*m_m[2] + in.y*m_m[6] + in.z*m_m[10] + m_m[14];
    float w=m_m[4] + m_m[7] + m_m[11] + m_m[15];
    // Homogenize
    w = 1/w;
    x *= w;
    y *= w;
    z *= w;
    out.Set(x,y,z);
}

/////////////////////////////////////////////////////////////////////////////
// Name:           GetA, GetB, GetC, GetD
// Arguments:      A vector to store the A, B, C vectors or
//                 a point to store the D position
// Returns:        none
// Side Effects:   'out' is set to the result.
/////////////////////////////////////////////////////////////////////////////
void Matrix::GetA(Vector3 &out) 
{
    out.Set(m_m[0], m_m[1], m_m[2]);
}
void Matrix::GetB(Vector3 &out)
{
    out.Set(m_m[4], m_m[5], m_m[6]);
};
void Matrix::GetC(Vector3 &out)
{
    out.Set(m_m[8], m_m[9], m_m[10]);
};
void Matrix::GetD(Point3  &out) 
{
    out.Set(m_m[12], m_m[13], m_m[14]);
};

/////////////////////////////////////////////////////////////////////////////
// Name:           SetA, SetB, SetC, SetD
// Arguments:      Three floats representing the three entries in the
//                 A,B,C, vectors or D position
// Returns:        none
// Side Effects:   Sets the appropriate entries in this matrix
/////////////////////////////////////////////////////////////////////////////
void Matrix::SetA(float ax, float ay, float az) 
{
    m_m[0]=ax,  m_m[1]=ay,  m_m[2]=az;
}
void Matrix::SetB(float bx, float by, float bz)         
{
    m_m[4]=bx,  m_m[5]=by,  m_m[6]=bz;
}

void Matrix::SetC(float cx, float cy, float cz)         
{
    m_m[8]=cx,  m_m[9]=cy,  m_m[10]=cz;
}
void Matrix::SetD(float dx, float dy, float dz)
{
    m_m[12]=dx,  m_m[13]=dy,  m_m[14]=dz;
}


/////////////////////////////////////////////////////////////////////////////
// Name:           MakeRotateX
// Arguments:      Angle in radians
// Returns:        none
// Side Effects:   Makes this matrix a rotation matrix about the X axis. 
//                 The translational components are set to 0.
/////////////////////////////////////////////////////////////////////////////
void Matrix::MakeRotateX(float t) {
    float cost=cosf(t);
    float sint=sinf(t);

    SetA(1.0f, 0.0f, 0.0f);
    SetB(0.0f, cost, sint);
    SetC(0.0f,-sint, cost);
    SetD(0,0,0);

    // Since we rarely use these entries any way, we'll comment out the last 
    // row as an optimization.  
    //m_m[0][3]=m_m[1][3]=m_m[2][3]=0;m_m[3][3]=1;
}

/////////////////////////////////////////////////////////////////////////////
// Name:           MakeRotateY
// Arguments:      Angle in radians
// Returns:        none
// Side Effects:   Makes this matrix a rotation matrix about the Y axis.  
//                 The translational components are set to 0.
/////////////////////////////////////////////////////////////////////////////
void Matrix::MakeRotateY(float t) {
    float cost=cosf(t);
    float sint=sinf(t);

    SetA(cost, 0.0f,-sint);
    SetB(0.0f, 1.0f, 0.0f);
    SetC(sint, 0.0f, cost);
    SetD(0,0,0);

    // Since we rarely use these entries any way, we'll comment out the last 
    // row as an optimization.  
    //m_m[0][3]=m_m[1][3]=m_m[2][3]=0;m_m[3][3]=1;
}

/////////////////////////////////////////////////////////////////////////////
// Name:           MakeRotateZ
// Arguments:      Angle in radians
// Returns:        none
// Side Effects:   Makes this matrix a rotation matrix about the Z axis.  
//                 The translational components are set to 0.
/////////////////////////////////////////////////////////////////////////////
void Matrix::MakeRotateZ(float t) {
    float cost=cosf(t);
    float sint=sinf(t);

    SetA(cost, sint, 0.0f);
    SetB(-sint, cost, 0.0f);
    SetC(0.0f, 0.0f, 1.0f);
    SetD(0,0,0);

    // Since we rarely use these entries any way, we'll comment out the last 
    // row as an optimization.  
    //m_m[0][3]=m_m[1][3]=m_m[2][3]=0;m_m[3][3]=1;
}

/////////////////////////////////////////////////////////////////////////////
// Name:           MakeRotateUnitAxis
// Arguments:      Unit vector v and the angle to rotate by in radians
// Returns:        none
// Side Effects:   Makes this matrix a rotation matrix about the 'v' axis. 
//                 The translational components are set to 0.
/////////////////////////////////////////////////////////////////////////////
void Matrix::MakeRotateUnitAxis(const Vector3 &v,float t) {
    float cost=cosf(t);
    float sint=sinf(t);
    float omc=1.0f-cost;

    m_m[0]=omc*v.x*v.x+cost;
    m_m[5]=omc*v.y*v.y+cost;
    m_m[10]=omc*v.z*v.z+cost;
    m_m[1]=omc*v.x*v.y+sint*v.z;
    m_m[4]=omc*v.x*v.y-sint*v.z;
    m_m[2]=omc*v.x*v.z-sint*v.y;
    m_m[8]=omc*v.x*v.z+sint*v.y;
    m_m[6]=omc*v.y*v.z+sint*v.x;
    m_m[9]=omc*v.y*v.z-sint*v.x;
    SetD(0,0,0);

    // Since we rarely use these entries any way, we'll comment out the last 
    // row as an optimization.  
    //m_m[0][3]=m_m[1][3]=m_m[2][3]=0;m_m[3][3]=1;
}


/////////////////////////////////////////////////////////////////////////////
// Name:           MakeScale
// Arguments:      Three scale factors for x, y, and z
// Returns:        none
// Side Effects:   Makes this matrix a scale matrix in x, y, and z;  
//                 The translational components are set to 0.
/////////////////////////////////////////////////////////////////////////////
void Matrix::MakeScale(float x,float y,float z) {
    SetA(x,0.0f,0.0f);
    SetB(0.0f,y,0.0f);
    SetC(0.0f,0.0f,z);
    SetD(0,0,0);


    // Since we rarely use these entries any way, we'll comment out the last 
    // row as an optimization.  
    //m_m[0][3]=m_m[1][3]=m_m[2][3]=0;m_m[3][3]=1;
}


/////////////////////////////////////////////////////////////////////////////
// Name:           MakeTranslate
// Arguments:      Three translations for x, y, and z
// Returns:        none
// Side Effects:   Makes this matrix a translation matrix in x, y, and z;  
//                 The remainder of the entries appear as in the identity 
//                 matrix
/////////////////////////////////////////////////////////////////////////////
void Matrix::MakeTranslate(float x,float y,float z) {
    Identity(); 
    SetD(x,y,z);

}

/////////////////////////////////////////////////////////////////////////////
// Name:           Translate
// Arguments:      A direction
// Returns:        none
// Side Effects:   Applies a translation v to d vector of this matrix
/////////////////////////////////////////////////////////////////////////////
void Matrix::Translate(const Vector3 &v) 
{
    m_m[12] += v.x; m_m[13] += v.y; m_m[14] += v.z;
}

//************************** End Assignment *********************************
//**************** Do not alter anything past this line *********************
//***************************************************************************





/////////////////////////////////////////////////////////////////////////////
// Name:           Transpose
// Arguments:      none
// Returns:        none
// Side Effects:   Transpose the current matrix
/////////////////////////////////////////////////////////////////////////////
void Matrix::Transpose() {
    float t;
    t=m_m[1];  m_m[1]=m_m[4];   m_m[4]=t;
    t=m_m[2];  m_m[2]=m_m[8];   m_m[8]=t;
    t=m_m[3];  m_m[3]=m_m[12];  m_m[12]=t;
    t=m_m[6];  m_m[6]=m_m[9];   m_m[9]=t;
    t=m_m[7];  m_m[7]=m_m[13];  m_m[13]=t;
    t=m_m[11]; m_m[11]=m_m[14]; m_m[14]=t;
}



/////////////////////////////////////////////////////////////////////////////
// Name:           Print
// Arguments:      string for debugging information
// Returns:        none
// Side Effects:   Prints out the current matrix and any info string before it
//                 (typically the name of the matrix).
/////////////////////////////////////////////////////////////////////////////
void Matrix::Print(const char *s) const {
    if(s) printf("%s={\n",s);
    else printf("matrix={\n");
    for(int i = 0; i < 4; i++) {
        printf("%f,%f,%f,%f\n",m_m[i],m_m[4+i],m_m[8+i],m_m[12+i]);         
    }

    printf("}\n");
}

////////////////////////////////////////////////////////////////////////////////