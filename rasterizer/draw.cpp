#include "draw.h"
#include "vector.h"

void drawLine()
{

    glBegin(GL_LINE_STRIP);
        for(int i = -50; i < 50; i++)
	{
	    Point3 p = Point3(i, i, -4);
	    glColor3f(1,0,0);
	    glVertex3fv(p);
	}
    glEnd();
}
