#include <GL/glut.h>

#ifndef CGR_WOBJECT_H
 #define CGR_WOBJECT_H

namespace cgrobot {
class WorldObject
{
public:
    virtual void update() = 0;
    virtual void draw() = 0;
};
}

#endif
