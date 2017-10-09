#include "Camera.hpp"
#include <iostream>

using namespace cgrobot;

Camera::Camera(GLdouble x, GLdouble y, GLdouble z)
      : m_eyeX(x), m_eyeY(y), m_eyeZ(z)
{}

void Camera::position(GLdouble x, GLdouble y, GLdouble z)
{ m_eyeX = x; m_eyeY = y; m_eyeZ = z; }

void Camera::lookAt(GLdouble x, GLdouble y, GLdouble z)
{ m_cntX = x; m_cntY = y; m_cntZ = z; }

void Camera::up(GLdouble x, GLdouble y, GLdouble z)
{ m_upX = x; m_upY = y; m_upZ = z; }

void Camera::turn(GLdouble dg)
{
    m_rotation -= dg;
}

void Camera::activate()
{
    glRotatef(m_rotation, 0, 1, 0);

    gluLookAt(
        m_eyeX, m_eyeY, m_eyeZ,
        m_cntX, m_cntY, m_cntZ,
        m_upX , m_upY , m_upZ
    );
}
