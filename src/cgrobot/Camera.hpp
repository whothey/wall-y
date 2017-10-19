#include <GL/glut.h>
#include <cmath>

#ifndef CGR_CAMERA_H
 #define CGR_CAMERA_H

namespace cgrobot {
class Camera
{
    GLdouble m_eyeX, m_eyeY, m_eyeZ,
             m_cntX, m_cntY, m_cntZ,
             m_upX , m_upY , m_upZ,
             m_vrotation, m_hrotation;
public:
    Camera(GLdouble x, GLdouble y, GLdouble z);
    void position(GLdouble x, GLdouble y, GLdouble z);
    void lookAt(GLdouble x, GLdouble y, GLdouble z);
    void up(GLdouble x, GLdouble y, GLdouble z);
    void turn(GLdouble dgh, GLdouble dgv);
    void turnH(GLdouble dg);
    void turnV(GLdouble dg);
    void activate();
};
}

#endif
