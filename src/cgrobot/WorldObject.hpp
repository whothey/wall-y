#ifndef _CGR_WOBJECT_H
 #define _CGR_WOBJECT_H

#include <GL/glut.h>
#include <cmath>
#include "../bmp.hpp"
#include "../helpers.c"

#define MAX_TEXTURES 5
#define TEXTURE "../textures/"

namespace cgrobot {
class WorldObject
{
protected:
    GLuint m_textures[MAX_TEXTURES];

public:
    GLdouble
        posX = 0, posY = 0, posZ = 0,
        rotX, rotY, rotZ;

    WorldObject();
    virtual void draw();
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void setPosition(GLdouble x, GLdouble y, GLdouble z);
    virtual void move(GLdouble x, GLdouble y, GLdouble z);
    virtual void turn(GLdouble x, GLdouble y, GLdouble z);
    virtual void turnX(GLdouble dg);
    virtual void turnY(GLdouble dg);
    virtual void turnZ(GLdouble dg);
};
}

#endif // _CGR_WOBJECT_H
