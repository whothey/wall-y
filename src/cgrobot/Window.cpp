#include "Window.hpp"

using namespace cgrobot;

Window::Window(int *argc, char **argv) : m_sizeW(300), m_sizeH(300) {
    glutInit(argc, argv);
}

Window::~Window() {
    glutDestroyWindow(m_idWindow);
}

void Window::setSize(int w, int h) { m_sizeW = w; m_sizeH = h; }
void Window::setPosition(int x, int y) { m_wX = x; m_wY = y; }
void Window::setDisplayModes(unsigned int modes) { m_modes = modes; }
void Window::setDisplayFunc(void (*fn)(void)) { m_DisplayFunc = fn; }
void Window::setReshapeFunc(void (*fn)(GLint, GLint)) { m_ReshapeFunc = fn; }
void Window::setKeyboardFunc(void (*fn)(unsigned char, int, int)) { m_KeyboardFunc = fn; }
void Window::setSpecialFunc(void (*fn)(int, int, int)) { m_SpecialFunc = fn; }

void Window::init()
{
    glutInitDisplayMode(m_modes);
    glutInitWindowSize(m_sizeW, m_sizeH);
    glutInitWindowPosition(m_wX, m_wY);
    glShadeModel(GL_SMOOTH);
    m_idWindow = glutCreateWindow(name);
    glutSetWindow(m_idWindow);
}

void Window::start()
{
    glutDisplayFunc(m_DisplayFunc);
    glutReshapeFunc(m_ReshapeFunc);
    glutKeyboardFunc(m_KeyboardFunc);
    glutSpecialFunc(m_SpecialFunc);
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    float vAmbientLightBright[4] = {.5f, .5f, .5f, .5f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, vAmbientLightBright);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glutMainLoop();
}

void Window::setCamera(Camera *c)
{
    
}
