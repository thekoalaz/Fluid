#include "scene.h"

using namespace Scene;
/** Global variables **/
int Object::NEXTID = 0;

void World::draw()
{
    for(std::vector<Object *>::const_iterator object = _objects.begin() ;
        object < _objects.end() ; object++)
    {
        (*object)->draw();
    }
}

void Object::draw()
{
	glTranslated(_tx, _ty, _tz);
	glRotated(_rotx,1,0,0);
	glRotated(_roty,0,1,0);
    glRotated(_rotz,0,0,1);
}

void Camera::draw()
{
}

void Grid::draw()
{
    glPushMatrix();
    Object::draw();
    for(int r = -(_rows/2); r <= (_rows/2); r++)
    {
        GlutDraw::drawLine(-(_cols/2.)*_gap, 0, r*_gap,
            (_cols/2.)*_gap, 0, r*_gap);
    }
    for(int c = -(_cols/2); c <= (_cols/2); c++)
    {
        GlutDraw::drawLine(c*_gap, 0, -(_rows/2.)*_gap,
            c*_gap, 0, (_rows/2.)*_gap);
    }
    glPopMatrix();
}

World & Scene::createWorld()
{
    World * new_world = new World();
    return *new_world;
}