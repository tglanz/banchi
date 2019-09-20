#include "BsApplication.h"
int main()
{
    using namespace bs;
    VideoMode videoMode(1280, 720);
    Application::startUp(videoMode, "Example", false);
    Application::instance().runMainLoop();
    Application::shutDown();
    return 0;
}