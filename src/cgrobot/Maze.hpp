#ifndef _CGR_MAZE_H
 #define _CGR_MAZE_H

#include <GL/glut.h>
#include "WorldObject.hpp"
#include "../helpers.c"

// Sim, eu estava com preguiça de copiar codigo por codigo
#define MAZE_WALLFACE_NORMAL(a, b, c) \
    VEC(v1, verts[a], verts[b]); \
    VEC(v2, verts[c], verts[a]); \
    CROSS(normal, v2, v1); \
    NORMALIZE(normal); \
    glNormal3dv(normal);

// Sim, eu estava com preguiça de copiar codigo por codigo
#define MAZE_WALLFACE(a, b, c, d) \
    MAZE_WALLFACE_NORMAL(a, b, c); \
    glTexCoord2f(0, 1.0f);    glVertex3dv(verts[a]); \
    glTexCoord2f(0, 0);       glVertex3dv(verts[b]); \
    glTexCoord2f(1.0f, 0);    glVertex3dv(verts[c]); \
    glTexCoord2f(1.0f, 1.0f); glVertex3dv(verts[d]); \

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
    void drawGround();
    void setAscpect(GLdouble a);

    GLdouble indexX(size_t i, size_t j);
    GLdouble indexY(size_t i, size_t j);
    GLdouble indexZ(size_t i, size_t j);

    size_t getRows();
    size_t getCols();

    virtual void init();
    virtual void draw();
    virtual void update();
};
}
#endif // _CGR_MAZE_H
