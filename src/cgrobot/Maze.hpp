#include <GL/glut.h>
#include "WorldObject.hpp"

namespace cgrobot {
class Maze : public WorldObject
{
    GLint *m_matrix;
    size_t m_matrixRows, m_matrixCols;
    GLdouble m_cubeHeight, m_cubeAspect;
    GLint index(size_t i, size_t j);

public:
    GLUquadricObj *wallQuadric;
    GLdouble startX, startY;

    Maze(GLint *adjMatrix, size_t nrows, size_t ncols);
    ~Maze();

    void loadFromMatrix(GLint *adjMatrix, size_t nrows, size_t ncols);
    virtual void draw();
    virtual void update();
};
}
