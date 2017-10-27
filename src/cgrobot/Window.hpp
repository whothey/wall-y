#ifndef _CGR_WINDOW_H
 #define _CGR_WINDOW_H

#include <GL/glut.h>
#include "Camera.hpp"
#include "WorldObject.hpp"

namespace cgrobot {
class Window {
    GLint m_sizeW, m_sizeH, m_wX, m_wY, m_idWindow;
    void
        (*m_IdleFunc)(void),
        (*m_DisplayFunc)(void),
        (*m_ReshapeFunc)(GLint, GLint),
        (*m_KeyboardFunc)(unsigned char, int, int),
        (*m_SpecialFunc)(int, int, int);
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

    //virtual void draw();
    //virtual void reshape();
};
}

#endif // _CGR_WINDOW_H
