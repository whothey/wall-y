#include "WorldObject.hpp"

using namespace cgrobot;

WorldObject::WorldObject()
     : posX(0), posY(0), posZ(0)
     , rotX(0), rotY(0), rotZ(0)
{ }

inline void WorldObject::setPosition(GLdouble x, GLdouble y, GLdouble z)
{ posX = x, posY = y, posZ = z; }

void WorldObject::draw()
{
    glTranslatef(posX, posY, posZ);

    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);
}

void WorldObject::move(GLdouble x, GLdouble y, GLdouble z)
{
    GLdouble radRotY = rotY * M_PI / 180.0f;

    posX += x * cos(radRotY) + z * sin(radRotY);
    posY += y;
    posZ += -x * sin(radRotY) + z * cos(radRotY);
}

void WorldObject::turn(GLdouble x, GLdouble y, GLdouble z)
{
    turnX(x); turnY(y); turnZ(z);
}

void WorldObject::turnX(GLdouble dg) { rotX += dg; }
void WorldObject::turnY(GLdouble dg) { rotY += dg; }
void WorldObject::turnZ(GLdouble dg) { rotZ += dg; }
