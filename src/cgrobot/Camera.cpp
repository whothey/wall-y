#include "Camera.hpp"
#include <iostream>

using namespace cgrobot;

Camera::Camera(GLdouble x, GLdouble y, GLdouble z)
      : m_eyeX(x), m_eyeY(y), m_eyeZ(z), m_vrotation(0), m_hrotation(0)
{}

void Camera::position(GLdouble x, GLdouble y, GLdouble z)
{ m_eyeX = x; m_eyeY = y; m_eyeZ = z; }

void Camera::lookAt(GLdouble x, GLdouble y, GLdouble z)
{ m_cntX = x; m_cntY = y; m_cntZ = z; }

void Camera::up(GLdouble x, GLdouble y, GLdouble z)
{ m_upX = x; m_upY = y; m_upZ = z; }

void Camera::turn(GLdouble dgh, GLdouble dgv)
{
    turnH(dgh);
    turnV(dgv);
}

void Camera::turnH(GLdouble dg)
{
    m_hrotation += dg;
}

void Camera::turnV(GLdouble dg)
{
    m_vrotation += dg;
}

void Camera::activate()
{
    glRotatef(m_vrotation, 0, 1, 0);
    glRotatef(m_hrotation, 1, 0, 0);

    gluLookAt(
        m_eyeX, m_eyeY, m_eyeZ,
        m_cntX, m_cntY, m_cntZ,
        m_upX , m_upY , m_upZ
    );
}
