#include "draw.h"
#include "vector.h"

void draw_point(float x0, float y0)
{
    Point3 p = Point3((int)x0, (int)(y0), 0);
    glColor3f(1,0,0);
    glVertex3fv(p);
}

void dda(float x0, float y0, float x1, float y1)
{

    float k, x, y;

    k = (y1 - y0) / (x1 - x0);

    x = x0;
    y = y0;

    for(int i = 0; i < x1; i++)
    {
	if(k < 1)
            draw_point(x++, y+=k + 0.5);
	else
	    for(int j = 0; j < k; j++)
                draw_point(x, y+=1 + 0.5);
    }

}

void middle_point(float x0, float y0, float x1, float y1)
{
    float A, B;
    float d, d1, d2, d3;
    float x, y;

    A = (y1 - y0);
    B = (x1 - x0);
    d = 2 * A + B;
    d1 = 2 * A;
    d2 = 2 * (A + B);
    d3 = 2 * B;

    draw_point(x0, y0);

    x = x0;
    while(x < x1)
    {
	if(d > 0)
	    x++, y++, d+= d2;
	//else if(d < -2)
	//    y++, d+= d3;
	else 
	    x++, d+= d1;
	draw_point(x, y);
    }
}

void bresenham(float x0, float y0, float x1, float y1)
{
    float x, y;
    float dx, dy, e;
    float d2x, d2y;

    dx = x1 - x0;
    dy = y1 - y0;

    e = -dx;

    d2y = 2 * dy;
    d2x = 2 * dx;

    x = x0;
    y = y0;
    draw_point(x, y);

    while(x < x1)
    {
	e += d2y;
	if(e > 0)
	    e -= d2x, draw_point(x++, y++);
	else
	    draw_point(x++, y);
    }
}

void fill_polygon(Polygon &p)
{

}
