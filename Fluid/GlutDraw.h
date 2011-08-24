#include "stdafx.h"

namespace GlutDraw
{

void drawLine(double x1, double y1, double z1,
        double x2, double y2, double z2)
{
    glBegin(GL_LINES);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
    glEnd();
}
}