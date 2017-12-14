#include "Light.hpp"

using namespace cgrobot;

Light::Light(int glLight) { m_lightSource = glLight; }
void Light::init() { }
Light::~Light() { }

void Light::enable() { enabled = true; }
void Light::disable() { enabled = false; }

void Light::setDirection(GLdouble x, GLdouble y, GLdouble z)
{ direction[0] = x, direction[1] = y, direction[2] = z; }

void Light::draw()
{
    GLfloat position[3] = { posX, posY, posZ };

    glEnable(GL_LIGHTING);

    if (enabled)
        glEnable(m_lightSource);
    else
        glDisable(m_lightSource);

    glPushMatrix();
      WorldObject::draw();

      glLightf(m_lightSource, GL_SPOT_CUTOFF, spotCutoff);
      glLightf(m_lightSource, GL_SPOT_EXPONENT, spotExponent);
      glLightf(m_lightSource, GL_CONSTANT_ATTENUATION, constantAttenuation);
      glLightf(m_lightSource, GL_LINEAR_ATTENUATION, linearAttenuation);
      glLightf(m_lightSource, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
      glLightfv(m_lightSource, GL_SPOT_DIRECTION, direction);

      glLightfv(m_lightSource, GL_DIFFUSE, diffuse);
      glLightfv(m_lightSource, GL_SPECULAR, specular);
      glLightfv(m_lightSource, GL_AMBIENT, ambient);
      glLightfv(m_lightSource, GL_POSITION, position);
    glPopMatrix();
}

void Light::setSpecular(GLdouble r, GLdouble g, GLdouble b, GLdouble i)
{ specular[0] = r, specular[1] = g, specular[2] = b, specular[3] = i; }

void Light::setDiffuse(GLdouble r, GLdouble g, GLdouble b, GLdouble i)
{ diffuse[0] = r, diffuse[1] = g, diffuse[2] = b, diffuse[3] = i; }

void Light::setAmbient(GLdouble r, GLdouble g, GLdouble b, GLdouble i)
{ ambient[0] = r, ambient[1] = g, ambient[2] = b, ambient[3] = i; }

void Light::update() { }
