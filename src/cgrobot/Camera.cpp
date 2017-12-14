#include "Camera.hpp"
#include <iostream>
#include "../helpers.c"

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
    GLdouble oldX = posX, oldZ = posZ;

    WorldObject::turnY(dg);

    GLdouble rad = dg * M_PI / 180;

    posX = oldX * cos(rad) - oldZ * sin(rad);
    posZ = oldX * sin(rad) + oldZ * cos(rad);

    //glRotatef(0, 1, 0, rotY);

    std::cout << "Rotation " << rotY << " and pos: " << posX << std::endl;

    //turnOffset(dg);
}

void Camera::turnOffset(GLdouble dg)
{
    GLdouble oldX = offsetX, oldZ = offsetZ;

    GLdouble rad = dg * M_PI / 180;

    offsetX = oldX * cos(rad) - oldZ * sin(rad);
    offsetZ = oldX * sin(rad) + oldZ * cos(rad);

    //glRotatef(0, 1, 0, dg);

    std::cout << "Rotation " << rotY << " and offset: " << offsetX << std::endl;
}

void Camera::calcDirections()
{
    GLdouble norm, front[3], up[3], side[3];

    frontX = cos(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch)),
    frontY = sin(DEG_TO_RAD(pitch)),
    frontZ = sin(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch)),

    norm = sqrt(pow(frontX, 2) + pow(frontY, 2) + pow(frontZ, 2));

    frontX /= norm;
    frontY /= norm;
    frontZ /= norm;

    VECTORIZE(front, frontX, frontY, frontZ);
    VECTORIZE(up, m_upX, m_upY, m_upZ);

    CROSS(side, front, up);
    NORMALIZE(side);

    sideX = side[0];
    sideY = side[1];
    sideZ = side[2];
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

void Camera::moveForward(GLdouble distance)
{
    posX += frontX * distance;
    posY += frontY * distance;
    posZ += frontZ * distance;
}

void Camera::moveSide(GLdouble distance)
{
    posX += sideX * distance;
    posY += sideY * distance;
    posZ += sideZ * distance;
}

void Camera::activate()
{
    if (type == ThirdPerson) {
        calcDirections();

        gluLookAt(
            posX, posY, posZ,
            posX + frontX, posY + frontY, posZ + frontZ,
            m_upX , m_upY , m_upZ
        );
    } else {
        gluLookAt(
            posX, posY, posZ,
            m_cntX, m_cntY, m_cntZ,
            m_upX , m_upY , m_upZ
        );
    }
}

void Camera::draw() { activate(); }
