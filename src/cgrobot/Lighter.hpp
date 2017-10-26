#ifndef _CGR_LIGHTER_H
#define _CGR_LIGHTER_H

#include <GL/glut.h>
#include <cmath>
#include "WorldObject.hpp"

namespace cgrobot {
class Lighter : public WorldObject
{
public:
    Lighter(GLdouble x, GLdouble y, GLdouble z);
    ~Lighter();

    GLUquadricObj *quadric;
    GLdouble rotateEixo;

    void drawLighter();
    void update();
    void init();
    void draw();
};
}
#endif // _CGR_ROBOT_H
