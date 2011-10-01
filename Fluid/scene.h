#include "stdafx.h"
#include "GlutDraw.h"

namespace Scene
{
/** Global variables **/

class Object;

class World
{
public:
    World() { }

    void addObject(Object * obj) { _objects.push_back(obj); }

    //void removeObject(Object & obj) {  }

    void draw();
private:
    std::vector<Object *> _objects;
};

class Object
{
public:
/* Constructors */
    Object() : _tx(0), _ty(0), _tz(0), _rotx(0), _roty(0), _rotz(0), _visible(true)
        { _ObjectId = nextId(); }
    Object(double tx, double ty, double tz, double rotx, double roty, double rotz) : _tx(tx), _ty(ty), _tz(tz),
        _rotx(rotx), _roty(roty), _rotz(rotz), _visible(true)
        { _ObjectId = nextId(); }
    virtual void draw() = 0;

    /* getters */
    double getTx() { return _tx; } const
    double getTy() { return _ty; } const
    double getTz() { return _tz; } const
    double getRotx() { return _rotx; } const
    double getRoty() { return _roty; } const
    double getRotz() { return _rotz; } const
    bool getVisible() { return _visible; } const
    int getId() { return _ObjectId; } const

    /* setters */
    void setTx(double tx) { _tx = tx; }
    void setTy(double ty) { _ty = ty; }
    void setTz(double tz) { _tz = tz; }
    void setRotx(double rotx) { _rotx = rotx; }
    void setRoty(double roty) { _roty = roty; }
    void setRotz(double rotz) { _rotz = rotz; }
    void setVisible(bool visible) { _visible = visible; }

    /* Single line functions */
    int nextId() { return NEXTID++; }
private:
    static int NEXTID;
    int _ObjectId;
    double _tx, _ty, _tz;
    double _rotx, _roty, _rotz;
    bool _visible;
};

class Camera : public Object
{
public:
/* Constructors */
    Camera() : Object() { }

    void draw();
private:
};

class Grid : public Object
{
public:
/* Constructors */
    Grid() : Object(), _rows(10), _cols(10), _gap(1.0) { }

    void draw();

private:
    int _rows, _cols;
    double _gap;
};


World & createWorld();

};