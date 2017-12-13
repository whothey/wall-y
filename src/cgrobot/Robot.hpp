#ifndef _CGR_ROBOT_H
#define _CGR_ROBOT_H

#include <GL/glut.h>
#include <cmath>
#include "WorldObject.hpp"
#include "../helpers.c"

namespace cgrobot {
class Robot : public WorldObject
{
public:
    Robot(GLdouble x, GLdouble y, GLdouble z);
    ~Robot();

    GLUquadricObj *quadric;
    GLint headMoveDirection = 1;
    GLdouble rotateEixo, olhoX = 0.5, olhoY = 2.75, cabecaEixo, arm; 

    GLfloat
        eyeLightDirection[3] = {0., -1., 0.},
        eyeDiffuseLight[4] = {1., 1., 1., 0.8},
        eyeSpecularLight[4] = {1., 1., 1., 0.3};

    void drawEyes();
    void drawNeck();
    void drawBody();
    void drawArms();
    void drawWheels();

    void update();
    void init();
    void draw();

    void turn(GLdouble dg);
};
}
#endif // _CGR_ROBOT_H
