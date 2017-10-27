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

    //posX = obj->posX + offsetX;
    //posY = obj->posY + offsetY;
    //posZ = obj->posZ + offsetZ;

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

    std::cout << "Pos: (" << posX << ", " << posY << ", " << posZ << ")" << std::endl;
    posX = posX * cos(rad) - posZ * sin(rad);
    posZ = posX * sin(rad) + posZ * cos(rad);
    std::cout << "New Pos: (" << posX << ", " << posY << ", " << posZ << ")" << std::endl;

    turnOffset(dg);

    std::cout << "New Pos + Offset: (" << posX + offsetX << ", " << posY + offsetY << ", " << posZ + offsetZ << ")" << std::endl;
}

void Camera::turnOffset(GLdouble dg)
{
    GLdouble rad = dg * M_PI / 180;

    std::cout << "Offsets: (" << offsetX << ", " << offsetY << ", " << offsetZ << ")" << std::endl;

    offsetX = offsetX * cos(rad) - offsetZ * sin(rad);
    offsetY = offsetY;
    offsetZ = offsetX * sin(rad) + offsetZ * cos(rad);

    std::cout << "New offsets: (" << offsetX << ", " << offsetY << ", " << offsetZ << ")" << std::endl;
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
    gluLookAt(
        posX + offsetX, posY + offsetY, posZ + offsetZ,
        m_cntX, m_cntY, m_cntZ,
        m_upX , m_upY , m_upZ
    );
}

void Camera::draw() { activate(); }
