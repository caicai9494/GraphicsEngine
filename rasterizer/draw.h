#ifndef _DRAW_H
#define _DRAW_H
#include "core.h"

enum LINE_METHOD{
    DDA
};

void drawLine(LINE_METHOD method, float x0, float y0, float x1, float y1); 

#endif
