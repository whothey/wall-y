#ifndef _CGR_WINDOW_H
 #define _CGR_WINDOW_H

#include <GL/glut.h>
#include "Camera.hpp"
#include "WorldObject.hpp"

namespace cgrobot {
class Window {
    GLint m_sizeW, m_sizeH, m_wX, m_wY, m_idWindow;
    void
        (*m_IdleFunc)(void) = nullptr,
        (*m_DisplayFunc)(void) = nullptr,
        (*m_ReshapeFunc)(GLint, GLint) = nullptr,
        (*m_KeyboardFunc)(unsigned char, int, int) = nullptr,
        (*m_SpecialFunc)(int, int, int) = nullptr,
        (*m_MouseFunc)(int, int, int, int) = nullptr,
        (*m_MotionFunc)(int, int) = nullptr,
        (*m_PassiveMotionFunc)(int, int) = nullptr;
    unsigned int m_modes;

public:
    const char *name;

    Window(int *argc, char **argv);
    ~Window();

    void setSize(int w, int h);
    void setPosition(int x, int y);
    void setDisplayModes(unsigned int modes);
    void init();
    void start();
    void setCamera(Camera *c);
    void setIdleFunc(void (*)(void));
    void setDisplayFunc(void (*)(void));
    void setReshapeFunc(void (*)(GLint, GLint));
    void setKeyboardFunc(void (*)(unsigned char, int, int));
    void setSpecialFunc(void (*fn)(int, int, int));
    void setMouseFunc(void (*fn)(int, int, int, int));
    void setMotionFunc(void (*fn)(int, int));
    void setPassiveMotionFunc(void (*fn)(int, int));

    //virtual void draw();
    //virtual void reshape();
};
}

#endif // _CGR_WINDOW_H
