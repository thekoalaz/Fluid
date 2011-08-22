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
}

void Manager::drawElements()
{
    glutMainLoop();
    /*for(std::vector<Window *>::iterator window = _windows.begin() ;
        window < _windows.end() ; window++)
    {
        (*window)->draw();
    }*/
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
    mainWindow = this;
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
   	glutInitWindowSize(getWidth(), getHeight());
	glutInitWindowPosition(getXPos(), getYPos());
    
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
	// prevent divide by 0 error when minimised
	if(w==0) 
		h = 1;

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
        glLoadIdentity();
        glTranslatef(0, 0, -_camera->getTz());
	    glTranslatef(_camera->getTx(),_camera->getTy(),0);
	    glRotatef(_camera->getRotx(),1,0,0);
	    glRotatef(_camera->getRoty(),0,1,0);
        
        _world->draw();

        /* XY Grid */
        glBegin(GL_LINES);
	    for(int i=-5;i<=5;++i) {
		    glVertex3f(i,-5, -5);
		    glVertex3f(i,5, -5);

		    glVertex3f(5,i, -5);
		    glVertex3f(-5,i, -5);
	    }
	    glEnd();
        glPopMatrix();

    }
}

/** Button Class **/
/** Abstract class that defines the basic properties of an UI element
 *
**/

void Button::draw()
{
}

void Controls::Mouse::init()
{
    mainMouse = this;
    glutMouseFunc(Controls::Mouse::mouseFuncWrapper);
    glutMotionFunc(Controls::Mouse::motionFuncWrapper);
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
