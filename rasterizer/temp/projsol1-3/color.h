/////////////////////////////////////////////////////////////////////////////
// Color3.h
//
// Author: Alex Kozlowski (kman@graphics.ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
// Color3: A simple color class for storing rgb colors.  Has overloaded float*
//        operator so it can be passed directly to OpenGL.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef CSE167_COLOR_H__
#define CSE167_COLOR_H__

#include "core.h"
#include <math.h>

class Color3 {
////////////////////////////////
// Constructors/Destructors
public:
	Color3() 
		: r(0),g(0),b(0) {}

	Color3(float _r, float _g, float _b) 
		: r(_r), g(_g), b(_b) {}	
////////////////////////////////
// Local Procedures
public:
	// Reset the color
	inline void Set(float rr, float gg, float bb) {r=rr;g=gg;b=bb;};
	// True if the color is equal to black
	inline bool IsBlack() const;
	// Sums up all the colors into 1 float
	inline float Sum() const;
	// Component-wise product between two colors
	inline Color3 ArrayProd(const Color3 &c) const;
	// Accessors
	inline float operator[](int i) const    { return (&r)[i]; }
	inline float &operator[](int i)         { return (&r)[i]; }
	// Addition
	inline void operator+=(Color3 c);
	// Subtraction
	inline void operator-=(Color3 c);
	// Multiplication
	inline void operator*=(float f);
	// Component-wise product 
	inline void operator*=(Color3 c);
	// Scale Color
	inline Color3 operator*(float f) const;
	// For OpenGL
    operator float*() const                                   {return (float*)this;}

////////////////////////////////
// Member Variables
public:
	float r, g, b;
};

/////////////////////////////////////////////////////////////////////////////
// Inline Operators
//
inline bool Color3::IsBlack() const {
	return (r==0 && g==0 && b==0);
}
inline float Color3::Sum() const {
	return r+g+b;
}
inline Color3 Color3::ArrayProd(const Color3 &c) const {
	return Color3(r*c.r, g*c.g, b*c.b);
}

inline void Color3::operator+=(Color3 c) {
	r+=c.r; g+=c.g; b+=c.b;
}
inline void Color3::operator-=(Color3 c) {
	r-=c.r; g-=c.g; b-=c.b;
}
inline void Color3::operator*=(float f) {
	r*=f; g*=f; b*=f;
}
inline Color3 Color3::operator* (float f) const {
	return Color3(r*f, g*f, b*f);
}
inline void Color3::operator*=(Color3 c) {
	r=r*c.r, g=g*c.g, b=b*c.b;
}

inline Color3 operator*(float f, Color3 c) {
	return c*f;
}

inline Color3 operator+ (Color3 c1, Color3 c2) {
	return Color3(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);
}

inline Color3 operator- (Color3 c1, Color3 c2) {
	return Color3(c1.r-c2.r, c1.g-c2.g, c1.b-c2.b);
}

inline Color3 operator* (Color3 c1, Color3 c2) {
	return Color3(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b);
}


inline Color3 operator/ (Color3 c, float f) {
	return Color3(c.r/f, c.g/f, c.b/f);
}

#endif
