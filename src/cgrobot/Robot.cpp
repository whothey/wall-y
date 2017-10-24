#include "Robot.hpp"

using namespace cgrobot;

Robot::Robot(GLdouble x, GLdouble y, GLdouble z)
{
    quadric = gluNewQuadric();
    
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
}

Robot::~Robot()
{
    gluDeleteQuadric(quadric);
}

void Robot::draw()
{
    WorldObject::draw();

    glPushMatrix();

    // Draw
    // Golden - Head Top
    glColor3f(212/255.0f, 175/255.0f, 55/255.0f);
    gluCylinder(quadric, 4, 2, 1, 100, 100);

    // Red - "Eye"
    glColor3f(1, 0, 0);
    glTranslatef(0, 0, -0.5);
    gluCylinder(quadric, 4, 4, 0.5, 20, 8);

    // Golden - Head Bottom
    glColor3f(212/255.0f, 175/255.0f, 55/255.0f);
    glTranslatef(0, 0, -1);
    gluCylinder(quadric, 2, 4, 1, 100, 100);

    // Blue - Neck
    glColor3f(0, 0, 1);
    glTranslatef(0, 0, -1);
    gluCylinder(quadric, 2, 2, 2, 100, 100);

    // Red - Plate
    glColor3f(1, 0, 0);
    glTranslatef(0, 0, -2);
    glutSolidCube(4);

    // Blue - Left Arm
    glColor3f(0, 0, 1);
    glTranslatef(-2, 0, 0);
    glRotatef(45, 0, 1, 0);
    gluCylinder(quadric, 2, 2, 2, 10, 10);

    glPopMatrix();
}

void Robot::update()
{ }
