#include <GL/glut.h>
#include <cmath>
#include "WorldObject.hpp"

namespace cgrobot {
class Robot : public WorldObject
{
public:
    Robot(GLdouble x, GLdouble y, GLdouble z);
    ~Robot();

    GLUquadricObj *quadric;

    virtual void update();
    virtual void draw();
};
}
