#ifndef _CGR_LIGHT_H
#define _CGR_LIGHT_H

#include <GL/glut.h>
#include <cmath>
#include "WorldObject.hpp"

namespace cgrobot {
class Light : public WorldObject
{
    int m_lightSource;

public:
    bool enabled = true;
    GLfloat
        ambient[4]  = { 0, 0, 0, 1 },
        specular[4] = { 1, 1, 1, 1 },
        diffuse[4]  = { 1, 1, 1, 1 },
        direction[3] = { 0, 0, -1 },
        spotExponent = 0,
        spotCutoff   = 180,
        constantAttenuation = 1,
        linearAttenuation   = 0,
        quadraticAttenuation = 0;

    Light(int glLight);
    ~Light();

    void disable();
    void enable();
    void setDirection(GLdouble x, GLdouble y, GLdouble z);
    void setSpecular(GLdouble r, GLdouble g, GLdouble b, GLdouble i);
    void setDiffuse(GLdouble r, GLdouble g, GLdouble b, GLdouble i);
    void setAmbient(GLdouble r, GLdouble g, GLdouble b, GLdouble i);

    void update();
    void init();
    void draw();
};
}
#endif // _CGR_LIGHT_H
