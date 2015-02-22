#ifndef _DRAW_H
#define _DRAW_H
#include "core.h"

static void draw_point(float x0, float y0);

void dda(float x0, float y0, float x1, float y1);
void middle_point(float x0, float y0, float x1, float y1);
void bresenham(float x0, float y0, float x1, float y1);

/*
struct newEdge
{
    float ymax;
    float xmin;
    float inc;
}NewEdge;

struct activeEdge
{
    float x;
    float dx;
    float ymax;
}ActiveEdge;
*/

class Edge
{
    private:

	float x0;
	float y0;
	float x1;
	float y1;

    public:

	bool operator <(const Edge &rhs) const
	{
	    return min(y0,y1) < min(rhs.y0, rhs.y1);
	}

	Edge(float m0, float n0, float m1, float n1)
	{
	    x0 = m0;
	    y0 = n0;
	    x1 = m1;
	    y1 = n1;
	}

	friend ostream &operator <<(ostream& o, const Edge &e);
};
ostream &operator <<(ostream& o, const Edge &e)
{
    o << "(" << e.x0 << ", " << e.y0 << " )" << endl;
    o << "(" << e.x1 << ", " << e.y1 << " )" << endl;
    return o;
}

//typedef set<NewEdge*> NET;
//typedef vector<ActiveEdge*> AET;
typedef vector<Edge*> Polygon;

void fill_polygon(Polygon &p); 


#endif
