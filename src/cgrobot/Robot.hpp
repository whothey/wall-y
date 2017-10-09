#include <GL/glut.h>
#include <cmath>
#include "WorldObject.hpp"

namespace cgrobot {
class Robot : public WorldObject
{
    GLdouble m_posX, m_posY, m_posZ, m_rotation;

public:
    Robot(GLdouble x, GLdouble y, GLdouble z);
    ~Robot();

    GLUquadricObj *quadric;

    virtual void update();
    virtual void draw();

    void move(GLdouble x, GLdouble y, GLdouble z);
    void turn(GLdouble dg);
};
}
