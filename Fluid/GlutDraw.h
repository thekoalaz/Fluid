#ifndef GLUTDRAW_H
#define GLUTDRAW_H

#include "stdafx.h"

namespace GlutDraw
{

//void drawLine(double x1, double y1, double z1,
//        double x2, double y2, double z2)
//        {
//    glBegin(GL_LINES);
//        glVertex3d(x1, y1, z1);
//        glVertex3d(x2, y2, z2);
//    glEnd();
//}
//
////TODO PRIO: drawRectangle so that we can do buttons.
//void drawRectangle(double x, double y,
//        double width, double height)
//        {
//    glBegin(GL_QUADS);
//        glVertex2d(x, y);
//        glVertex2d(x + width, y);
//        glVertex2d(x, y + height);
//        glVertex2d(x + width, y + height);
//    glEnd();
//}

void drawLine(double x1, double y1, double z1,
        double x2, double y2, double z2);

//TODO PRIO: drawRectangle so that we can do buttons.
void drawRectangle(double x, double y,
        double width, double height);

};
#endif /* GLUTDRAW_H */