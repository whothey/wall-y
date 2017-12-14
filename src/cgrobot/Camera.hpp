#ifndef CGR_CAMERA_H
 #define CGR_CAMERA_H

#include <GL/glut.h>
#include <cmath>
#include "WorldObject.hpp"

namespace cgrobot {

enum CameraType { 
    Locked,
    ThirdPerson
};

class Camera : public WorldObject
{
    GLdouble 
        m_cntX, m_cntY, m_cntZ,
        m_upX , m_upY , m_upZ,
        m_followX, m_followY, m_followZ,
        m_vrotation, m_hrotation;

public:
    GLdouble offsetX, offsetY, offsetZ;
    GLdouble pitch, yaw, roll, frontX, frontY, frontZ, sideX, sideY, sideZ;

    CameraType type = Locked;

    WorldObject *following = nullptr;

    Camera(GLdouble x, GLdouble y, GLdouble z);
    void position(GLdouble x, GLdouble y, GLdouble z);

    void lookAt(GLdouble x, GLdouble y, GLdouble z);
    void lookAt(WorldObject *obj);

    void follow(WorldObject *obj);
    void inline unfollow();
    void turnOffset(GLdouble dg);
    void moveOffset(GLdouble x, GLdouble y, GLdouble z);

    void up(GLdouble x, GLdouble y, GLdouble z);
    void turn(GLdouble dgh, GLdouble dgv);
    void turnY(GLdouble dg);
    void turnH(GLdouble dg);
    void turnV(GLdouble dg);

    void calcDirections();
    void moveForward(GLdouble);
    void moveSide(GLdouble);

    void init();
    void draw();
    void activate();
    void update();
};
}

#endif
