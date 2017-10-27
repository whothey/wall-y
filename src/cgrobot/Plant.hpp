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
<<<<<<< HEAD
    GLdouble rotateEixo=0;
=======
>>>>>>> 93164c3ea2a9097a42349864af42395ccb8fb52c

    void drawGreen  ();
    void drawBoot();

    void update();
    void init();
    void draw();
<<<<<<< HEAD

    void turn(GLdouble dg);
};
}
#endif // _CGR_ROBOT_H
=======
};
}
#endif // _CGR_PLANT_H
>>>>>>> 93164c3ea2a9097a42349864af42395ccb8fb52c
