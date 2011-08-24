// Fluid.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GlutUI.h"

GlutUI::Manager MANAGER;

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;
    MANAGER.init(argc, argv);
    GlutUI::Window & mainWindow = MANAGER.createWindow(640,480, "TestWindow");
    GlutUI::Panel & mainPanel = MANAGER.createPanel(mainWindow, 640,480, "TestPanel");
    Scene::World world = Scene::createWorld();
    mainPanel.setWorld(&world);

    Scene::Grid * gridXZ = new Scene::Grid();
    world.addObject(gridXZ);
    gridXZ->setTy(-5);

    Scene::Grid * gridXY = new Scene::Grid();
    world.addObject(gridXY);
    gridXY->setRotx(90);
    gridXY->setTz(-5);

    Scene::Grid * gridYZ = new Scene::Grid();
    world.addObject(gridYZ);
    gridYZ->setRotz(90);
    gridYZ->setTx(-5);

    mainPanel.setWorld(&world);
    mainPanel.setCamera(new Scene::Camera());
    GlutUI::Controls::Mouse(mainPanel.getCamera());

    glEnable(GL_DEPTH_TEST);
    MANAGER.drawElements();
	return 0;
}
