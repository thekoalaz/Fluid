/** Display.h
 * This header defines with the main functionality of windows and displays.
 *
 * 
**/

#include "stdafx.h"
#include "scene.h"

namespace GlutUI
{
#define DEFAULT_XPOS 10
#define DEFAULT_YPOS 10
#define DEFAULT_WINDOWNAME "A Window"


/** Global variables **/

/** Class Prototypes **/
class Manager;
class UIElement;
class Window;
class Panel;
class Button;

/** Class Definitions **/

/** Manager Class **/
/** Manages and exposes all the UI elements.
 * There should only ever be one manager.
**/
class Manager
{
public:
    /* Constructors */
    Manager() { }

    void init(int argc, char* argv[]);
    void display();
    void drawElements();

    Window & createWindow(int width, int height);
    Window & createWindow(int width, int height, std::string name);
    Window & createWindow(int width, int height, int xpos, int ypos, std::string name);

    Panel & createPanel(Window & window, int width, int height, std::string name);
    Panel & createPanel(Window & window, int width, int height, int xpos, int ypos, std::string name);

private:
    std::vector<Window *> _windows;
    std::vector<UIElement *> _elements;
};

/** Display Functor Class **/
/** 
 *
**/
//class Display_Class
//{
//public:
//    Display_Class(Manager * manager) : _manager(manager) { }
//
//    void operator() () const { _manager->drawElements(); }
//private:
//    Manager * _manager;
//};

/** UIElement Class **/
/** Abstract class that defines the basic properties of an UI element
 *
**/
class UIElement
{
public:
    /* Constructors */
    UIElement(int width, int height)
        : _xpos(DEFAULT_XPOS), _ypos(DEFAULT_YPOS), _width(width), _height(height), _name(NULL)
        { init(); }
    UIElement(int width, int height, std::string name)
        : _xpos(DEFAULT_XPOS), _ypos(DEFAULT_YPOS), _width(width), _height(height), _name(name)
        { init(); }
    UIElement(int xpos, int ypos, int width, int height, std::string name)
        : _xpos(xpos), _ypos(ypos), _width(width), _height(height), _name(name)
        { init(); }

    
    virtual void init();
    virtual void draw() = 0;
    

    /* getters */
    int getXPos() { return _xpos; } const
    int getYPos() { return _ypos; } const
    int getWidth() { return _width; } const 
    int getHeight() { return _height; } const
    std::string getName() { return _name; } const
    int getId() { return _UIElemId; } const

    std::vector<UIElement *> & getChildren() { return _children; } const


    /* setters */
    void setXPos(int xpos) { _xpos=xpos; }
    void setYPos(int ypos) { _ypos=ypos; }
    void setWidth(int width) { _width=width; }
    void setHeight(int height) { _height=height; }
    void setName(std::string name) { _name=name; }

    void addChildren(UIElement * elem) { _children.push_back(elem); }

    /* Single line functions */
    int nextId() { return NEXTID++; }

private:
    int _xpos, _ypos,
        _width, _height;
    std::string _name;
    int _UIElemId;
    static int NEXTID;
    std::vector<UIElement *> _children;
};


/** Window Class **/
/** Abstract class that defines the basic properties of an UI element
 *
**/
class Window : public UIElement
{
public:
    /* Constructors */
    Window(int width, int height) : UIElement(width, height)
    { setName(DEFAULT_WINDOWNAME); init(); }
    Window(int width, int height, std::string name) : UIElement(width, height, name) { init(); }

    void init();
    void draw();
    void reshape(int w, int h);
    
private:
    static void displayFuncWrapper();
    static void reshapeFuncWrapper(int w, int h);
};


/** Panel Class **/
/** Panel class that defines a panel areas within the 
 *
**/
class Panel : public UIElement
{
public:
    Panel(int width, int height) : UIElement(width, height), _persp(false)
        { setName("Panel " + getId()); }
    Panel(int width, int height, std::string name) : UIElement(width, height, name), _persp(false)
        { setName("Panel " + getId()); }
    Panel(int width, int height, int xpos, int ypos, std::string name) : UIElement(width, height, xpos, ypos, name), _persp(false)
        { setName("Panel " + getId()); }
    void draw();

    void setWorld(Scene::World * world) { _world = world; }
    void setCamera(Scene::Camera * camera) { _camera = camera; }

    Scene::Camera * getCamera() { return _camera; }

private:
    std::vector<Button> _buttons;
    bool _persp;
    Scene::World * _world;
    Scene::Camera * _camera;
};


/** Button Class **/
/** Abstract class that defines the basic properties of an UI element
 *
**/
class Button : public UIElement
{
public:
    Button(int width, int height);
    Button(int width, int height, void *callback(void));
    void draw();

private:
};


namespace Controls
{
    class Mouse
    {
    public:
        Mouse(Scene::Camera * camera) : _camera(camera) { init(); }
        void init();
        void mouse(int button, int state, int x, int y);
        void motion(int x, int y);

    private:
        //TODO replace with actual camera:
        Scene::Camera * _camera;
        int _lastx, _lasty;
        bool _buttons[3];
        static void mouseFuncWrapper(int button, int state, int x, int y);
        static void motionFuncWrapper(int x, int y);
    };

    class Keyboard
    {
    };
}

};
