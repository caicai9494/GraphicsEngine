#include "draw.h"
#include "vector.h"

void drawLine(LINE_METHOD method, float x0, float y0, float x1, float y1)
{
    glBegin(GL_POINTS);

    switch(method)
    {
	case(DDA):

	    float k = (y1 - y0) / (x1 - x0);

	    float x, y;
	    x = x0;
	    y = y0;

	    for(int i = 0; i < 360; i++)
	    {

		Point3 p = Point3((int)x++, (int)(y+=k), 0);
		glColor3f(1,0,0);
		glVertex3fv(p);
	    }

	break;
	
    }

    glEnd();
}
