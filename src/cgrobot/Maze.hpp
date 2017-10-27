#ifndef _CGR_MAZE_H
 #define _CGR_MAZE_H

#include <GL/glut.h>
#include "WorldObject.hpp"

namespace cgrobot {
class Maze : public WorldObject
{
    GLint *m_matrix;
    size_t m_matrixRows, m_matrixCols;
    GLdouble m_cubeHeight, m_cubeAspect;
    GLint index(size_t i, size_t j);

    GLuint m_wallTexture;
    GLuint m_groundTexture;

public:
    GLUquadricObj *wallQuadric;
    GLdouble startX, startY;

    Maze();
    Maze(GLint *adjMatrix, size_t nrows, size_t ncols);
    ~Maze();

    void loadFromMatrix(GLint *adjMatrix, size_t nrows, size_t ncols);
    void drawWall();
    void setAscpect(GLdouble a);

    GLdouble indexX(size_t i, size_t j);
    GLdouble indexY(size_t i, size_t j);
    GLdouble indexZ(size_t i, size_t j);

    virtual void init();
    virtual void draw();
    virtual void update();
};
}
#endif // _CGR_MAZE_H
