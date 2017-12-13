#ifndef _CGR_WGLASS_H
#define _CGR_WGLASS_H

#include <GL/glut.h>
#include <cmath>
#include "WorldObject.hpp"

namespace cgrobot {
class WindowGlass : public WorldObject
{
public:
    WindowGlass(GLdouble x, GLdouble y, GLdouble z);
    ~WindowGlass();

    GLUquadricObj *quadric;
    GLdouble rotateEixo;

    void update();
    void init();
    void draw();
};
}
#endif // _CGR_WGLASS_H
