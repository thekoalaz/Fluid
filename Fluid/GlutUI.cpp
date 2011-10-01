/** Display.cpp
 * 
 *
 * 
**/

#include "GlutUI.h"

using namespace GlutUI;
/** Global variables **/
int UIElement::NEXTID = 0;
//TODO Hacks. Make sure these are actually the right window and controls.
Window * mainWindow;
Controls::Mouse * mainMouse;

/** Method Definitions **/

/** Manager Class **/
/** Manages and exposes all the UI elements
 *
**/

void Manager::init(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
     
    glEnable(GL_DEPTH_TEST);
}

void Manager::drawElements()
{
    glutMainLoop();
}

Window & Manager::createWindow(int width, int height)
{
    Window * new_window = new Window(width, height);
    _windows.push_back(new_window);
    return *new_window;
}

Window & Manager::createWindow(int width, int height, std::string name)
{
    Window * new_window = new Window(width, height, name);
    _windows.push_back(new_window);
    return *new_window;
}

Panel & Manager::createPanel(Window & window, int width, int height, std::string name)
{
    Panel * new_panel = new Panel(width, height, name);
    window.addChildren(new_panel);
    _elements.push_back(new_panel);

    return *new_panel;
}

Panel & Manager::createPanel(Window & window, int width, int height, int xpos, int ypos, std::string name)
{
    Panel * new_panel = new Panel(width, height, xpos, ypos, name);
    window.addChildren(new_panel);
    _elements.push_back(new_panel);

    return *new_panel;
}

Button & Manager::createButton(Panel & panel, int width, int height, int xpos, int ypos, std::string name)
{
    Button * new_button = new Button(width, height, xpos, ypos, name);
    panel.addChildren(new_button);
    _elements.push_back(new_button);

    return *new_button;
}

/** UIElement Class **/
/** Abstract class that defines the basic properties of an UI element
 *
**/

void UIElement::init()
{
     _UIElemId = nextId();
}

/** Window Class **/
/** Abstract class that defines the basic properties of an UI element
 *
**/

void Window::init()
{
    _init = false;
    mainWindow = this;
    glutInitWindowSize(getWidth(), getHeight());
    glutInitWindowPosition(getXPos(), getYPos());
    glutCreateWindow(getName().c_str());
    glutDisplayFunc(Window::displayFuncWrapper);
	glutReshapeFunc(Window::reshapeFuncWrapper);
}

void Window::displayFuncWrapper()
{
    mainWindow->draw();
}

void Window::reshapeFuncWrapper(int w, int h)
{
    mainWindow->reshape(w, h);
}

void Window::draw()
{    
    //std::cout << "Creating Window: " << getWidth() << " by " << getHeight() << "." << std::endl;

    glClearColor(0.2f, 0.2f, 0.2f, 0.0f); 
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    for(std::vector<UIElement *>::const_iterator child = getChildren().begin() ;
        child < getChildren().end() ; child++)
    {
        (*child)->draw();
    }
    
	glutSwapBuffers();
}

void Window::reshape(int w, int h)
{
    std::cout << "New size: " << w << " by " << h << std::endl;
	// prevent divide by 0 error when minimised
	if(w==0) 
		h = 1;

    setWidth(w);
    setHeight(h);
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/h,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/** Panel Class **/
/** Panel class that defines a panel areas within the 
 *
**/

void Panel::draw()
{
    if(_world != NULL)
    {
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45,(float)getWidth()/getHeight(),0.1,100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(0., 0., -_camera->getTz());
	    glTranslated(_camera->getTx(),_camera->getTy(),0.);
	    glRotated(_camera->getRotx(),1,0,0);
	    glRotated(_camera->getRoty(),0,1,0);
        
        _world->draw();

        glPopMatrix();
    }
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, getWidth(), getHeight(), 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    for(std::vector<UIElement *>::const_iterator child = getChildren().begin() ;
        child < getChildren().end() ; child++)
    {
        (*child)->draw();
    }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW); 
}

/** Button Class **/
/** Abstract class that defines the basic properties of an UI element
 *
**/

void Button::draw()
{
    //glPushMatrix();
    glColor4d(1.0, 1.0, 1.0, 0.2);
    GlutDraw::drawRectangle(getXPos(), getYPos(), getWidth(), getHeight());
    //
    //glColor4d(1.0, 1.0, 1.0, 0.2);
    //glBegin(GL_QUADS);
    //    glVertex2d(getXPos(), getYPos());
    //    glVertex2d(getXPos() + getWidth(), getYPos());
    //    glVertex2d(getXPos() + getWidth(), getYPos() + getHeight());
    //    glVertex2d(getXPos(), getYPos() + getHeight());
    //glEnd();
}

void Controls::Mouse::init()
{
    mainMouse = this;
    glutMouseFunc(Controls::Mouse::mouseFuncWrapper);
    glutMotionFunc(Controls::Mouse::motionFuncWrapper);
    //glutMouseWheelFunc(mouseWheel);
}

void Controls::Mouse::mouse(int button, int state, int x, int y)
{
    _lastx=x;
	_lasty=y;
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		_buttons[0] = ((GLUT_DOWN==state)? true : false);
        std::cout << "Left button pressed." << x << ", " << y << std::endl;
		break;

	case GLUT_MIDDLE_BUTTON:
		_buttons[1] = ((GLUT_DOWN==state)? true : false);
        std::cout << "Middle button pressed." << x << ", " << y << std::endl;
		break;

	case GLUT_RIGHT_BUTTON:
		_buttons[2] = ((GLUT_DOWN==state)? true : false);
        std::cout << "Right button pressed." << x << ", " << y << std::endl;
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void Controls::Mouse::motion(int x, int y)
{
    int diffx=x-_lastx;
	int diffy=y-_lasty;
	_lastx=x;
	_lasty=y;

	if(_buttons[0])
	{
        _camera->setRotx(_camera->getRotx() + (float) 0.5f * diffy);
		_camera->setRoty(_camera->getRoty() - (float) 0.5f * diffx);
	}
	else if(_buttons[2])
	{
        _camera->setTz( _camera->getTz() - (float) 0.05f * diffx);
	}
	else if(_buttons[1])
	{
        _camera->setTx(_camera->getTx() + (float) 0.05f * diffx);
        _camera->setTy(_camera->getTy() - (float) 0.05f * diffy);
	}
	glutPostRedisplay();
}

void Controls::Mouse::mouseFuncWrapper(int button, int state, int x, int y)
{
    mainMouse->mouse(button, state, x, y);
}

void Controls::Mouse::motionFuncWrapper(int x, int y)
{
    mainMouse->motion(x, y);
}

//TODO Keyboard functions