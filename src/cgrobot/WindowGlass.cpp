#include "WindowGlass.hpp"

using namespace cgrobot;

WindowGlass::WindowGlass(GLdouble x, GLdouble y, GLdouble z)
{
    posX = x, posY = y, posZ =z;

    quadric = gluNewQuadric();

    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
}

void WindowGlass::init()
{ }

WindowGlass::~WindowGlass()
{
    gluDeleteQuadric(quadric);
}


void WindowGlass::draw()
{
    glPushMatrix();
      WorldObject::draw();

      glTranslatef(4.5, 10, 0);

      glColor4f(1., 1., 1., .3);
      glutSolidCube(20);
    glPopMatrix();
}

void WindowGlass::update() {}
