#include "Camera.hpp"
#include <iostream>

using namespace cgrobot;

Camera::Camera(GLdouble x, GLdouble y, GLdouble z) : m_vrotation(0), m_hrotation(0)
{
    position(x, y, z);
}

void Camera::init() {}

void Camera::position(GLdouble x, GLdouble y, GLdouble z)
{ posX = x, posY = y, posZ = z; }

void Camera::lookAt(GLdouble x, GLdouble y, GLdouble z)
{
    m_cntX = x;
    m_cntY = y;
    m_cntZ = z;
}

void Camera::lookAt(WorldObject *obj) { lookAt(obj->posX, obj->posY, obj->posZ); }

void Camera::follow(WorldObject *obj)
{
    std::cout << "Following: (" << obj->posX << ", " << obj->posY << ", " << obj->posZ << ") ";

    following = obj;

    posX = obj->posX + offsetX;
    posY = obj->posY + offsetY;
    posZ = obj->posZ + offsetZ;

    m_followX = obj->posX;
    m_followY = obj->posY;
    m_followZ = obj->posZ;

    std::cout << "From: (" << posX << ", " << posY << ", " << posZ << ")" << std::endl;
}

void inline Camera::unfollow() { m_followX = m_followY = m_followZ = 0; }

void Camera::turnY(GLdouble dg)
{
    WorldObject::turnY(dg);

    GLdouble rad = rotY * M_PI / 180;

    posX = posX * cos(rad) - posZ * sin(rad);
    posZ = posX * sin(rad) + posZ * cos(rad);
}

void Camera::turnOffset(GLdouble dg)
{
    GLdouble rad = dg * M_PI / 180;
    GLdouble oldOffsetX = offsetX, oldOffsetZ = offsetZ;

    rotY += dg;

    //posX = (m_followX + offsetX) * cos(rad) - (m_followZ + offsetZ) * sin(rad);
    //posZ = (m_followX + offsetX) * sin(rad) + (m_followZ + offsetZ) * cos(rad);

    offsetX = offsetX * cos(rad) - offsetZ * sin(rad);
    offsetZ = offsetX * sin(rad) + offsetZ * cos(rad);

    posX -= oldOffsetX + offsetX;
    posZ -= oldOffsetZ + offsetZ;
}

void Camera::moveOffset(GLdouble x, GLdouble y, GLdouble z)
{
    GLdouble
        radRotY = rotY * M_PI / 180.0f,
        oldOffsetX = offsetX,
        oldOffsetY = offsetY,
        oldOffsetZ = offsetZ;

    offsetX += x * cos(radRotY) + z * sin(radRotY);
    offsetY += y;
    offsetZ += -x * sin(radRotY) + z * cos(radRotY);

    posX -= oldOffsetX + offsetX;
    posY -= oldOffsetY + offsetY;
    posZ -= oldOffsetZ + offsetZ;
}

void Camera::up(GLdouble x, GLdouble y, GLdouble z)
{ m_upX = x; m_upY = y; m_upZ = z; }

void Camera::update() { }

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
    //GLdouble radRotY = rotY * M_PI / 180, diffX, diffY, diffZ;

    //if (following != nullptr) {
    //    diffX = following->posX - m_followX;
    //    diffY = following->posY - m_followY;
    //    diffZ = following->posX - m_followX;

    //    posX += diffX * cos(radRotY) - diffZ * sin(radRotY);
    //    posY += diffY;
    //    posZ += diffX * sin(radRotY) + diffZ * cos(radRotY);

    //    if (diffX != 0 || diffY != 0 || diffZ != 0)
    //        std::cout << "Moving: (" << diffX << ", " << diffY << ", " << diffZ << ")" << std::endl;

    //    m_followX = following->posX;
    //    m_followY = following->posY;
    //    m_followZ = following->posZ;
    //}

    gluLookAt(
        posX, posY, posZ,
        m_cntX, m_cntY, m_cntZ,
        m_upX , m_upY , m_upZ
    );
}

void Camera::draw() { activate(); }
