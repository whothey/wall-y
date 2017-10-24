#include <GL/glut.h>

#ifndef CGR_WOBJECT_H
 #define CGR_WOBJECT_H

namespace cgrobot {
class WorldObject
{
    GLdouble
        posX, posY, posZ,
        rotX, rotY, rotZ;

public:
    WorldObject();
    virtual void draw();
    virtual void update() = 0;
    virtual void move(GLdouble x, GLdouble y, GLdouble z);
    virtual void turn(GLdouble x, GLdouble y, GLdouble z);
    virtual void turnX(GLdouble dg);
    virtual void turnY(GLdouble dg);
    virtual void turnZ(GLdouble dg);
};
}

#endif
