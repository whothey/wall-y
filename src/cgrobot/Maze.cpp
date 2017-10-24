#include "Maze.hpp"
#include <iostream>

using namespace cgrobot;


Maze::Maze(GLint *adjMatrix, size_t nrows, size_t ncols)
    : m_matrix(adjMatrix), m_matrixRows(nrows), m_matrixCols(ncols)
    , m_cubeHeight(10), m_cubeAspect(10)
{
    wallQuadric = gluNewQuadric();
    gluQuadricDrawStyle(wallQuadric, GLU_FILL);
}

Maze::~Maze()
{
    gluDeleteQuadric(wallQuadric);
}

GLint Maze::index(size_t i, size_t j) {
    size_t idx = i * m_matrixCols + j;

    return m_matrix[idx];
};

void Maze::loadFromMatrix(GLint *adjMatrix, size_t nrows, size_t ncols)
{ m_matrix = adjMatrix; m_matrixRows = nrows; m_matrixCols = ncols; }

void Maze::draw()
{
    size_t i, j;

    glColor3f(0, 1, 0);

    glPushMatrix();

    for (i = 0; i < m_matrixRows; i++) {
        glPushMatrix();
        for (j = 0; j < m_matrixCols; j++) {
            if (index(i, j) == 1) glutSolidCube(m_cubeAspect);
            glTranslatef(0, m_cubeAspect, 0);
        }
        glPopMatrix();

        glTranslatef(m_cubeAspect, 0, 0);
    }

    glPopMatrix();

    WorldObject::draw();
}

void Maze::update()
{
}
