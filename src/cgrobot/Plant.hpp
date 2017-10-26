#ifndef _CGR_PLANT_H
#define _CGR_PLANT_H

#include <GL/glut.h>
#include <cmath>
#include "WorldObject.hpp"

namespace cgrobot {
class Plant : public WorldObject
{
public:
    Plant(GLdouble x, GLdouble y, GLdouble z);
    ~Plant();

    GLUquadricObj *quadric;

    void drawGreen  ();
    void drawBoot();

    void update();
    void init();
    void draw();
};
}
#endif // _CGR_PLANT_H
