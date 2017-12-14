#include "Maze.hpp"
#include <iostream>

using namespace cgrobot;

Maze::Maze() : m_cubeHeight(10), m_cubeAspect(5) {};

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
    glDeleteTextures(1, &m_groundTexture);
    glDeleteTextures(1, &m_wallTexture);
}

GLint Maze::index(size_t i, size_t j) {
    size_t idx = i * m_matrixCols + j;

    return m_matrix[idx];
};

void Maze::loadFromMatrix(GLint *adjMatrix, size_t nrows, size_t ncols)
{ m_matrix = adjMatrix; m_matrixRows = nrows; m_matrixCols = ncols; }

void Maze::init()
{
    unsigned int
        wih = 0, wiw = 0,
        gih = 0, giw = 0;

    unsigned char *wallTextureImage, *groundTextureImage;

    wallTextureImage = loadBMP_custom(TEXTURE "grass.bmp", wih, wiw);
    groundTextureImage = loadBMP_custom(TEXTURE "ground.bmp", gih, giw);

    // Bytes per color
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &m_wallTexture);
    glBindTexture(GL_TEXTURE_2D, m_wallTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wiw, wih, 0, GL_RGB, GL_UNSIGNED_BYTE, wallTextureImage);
    //gluBuild2DMipmaps(m_wallTexture, GL_RGB, wiw, wih, GL_RGB, GL_UNSIGNED_BYTE, wallTextureImage);

    // Textura do chão
    glGenTextures(1, &m_groundTexture);
    glBindTexture(GL_TEXTURE_2D, m_groundTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, giw, gih, 0, GL_RGB, GL_UNSIGNED_BYTE, groundTextureImage);
    //gluBuild2DMipmaps(m_groundTexture, GL_RGB, giw, gih, GL_RGB, GL_UNSIGNED_BYTE, groundTextureImage);
}

void Maze::drawWall()
{
    GLdouble size        = m_cubeAspect / 2;
    GLdouble center[3]   = { size / 2, size / 2, 0 };

    glColor3f(0, 1, 0);

    GLdouble verts[8][3] = {
        { center[0] + size, center[1] + size, center[2] + size },  // A - 0
        { center[0] + size, center[1] - size, center[2] + size },  // B - 1
        { center[0] + size, center[1] - size, center[2] - size },  // C - 2
        { center[0] + size, center[1] + size, center[2] - size },  // D - 3
        { center[0] - size, center[1] + size, center[2] - size },  // E - 4
        { center[0] - size, center[1] - size, center[2] - size },  // F - 5
        { center[0] - size, center[1] + size, center[2] + size },  // G - 6
        { center[0] - size, center[1] - size, center[2] + size },  // H - 7
    };

    // Usados na macro MAZE_WALLFACE
    GLdouble v1[3], v2[3], normal[3];

    glBindTexture(GL_TEXTURE_2D, m_wallTexture);

    glBegin(GL_QUADS);
      MAZE_WALLFACE(4, 5, 7, 6); // Back
      MAZE_WALLFACE(7, 5, 2, 1); // Bottom
      MAZE_WALLFACE(6, 7, 1, 0); // Left
      MAZE_WALLFACE(3, 2, 5, 4); // Right
      MAZE_WALLFACE(6, 0, 3, 4); // Top
      MAZE_WALLFACE(0, 1, 2, 3); // Front
    glEnd();
}

void Maze::drawGround()
{
    GLdouble groundNormal[3] = { 0, 1, 0 };
    GLdouble starts = -m_cubeAspect / 4;

    glColor3f(213/255.0f, 208/255.0f, 178/255.0f);

    glPushMatrix();
        glTranslatef(starts, 0, starts * 2);

        glBindTexture(GL_TEXTURE_2D, m_groundTexture);

        glBegin(GL_QUADS);
          glNormal3dv(groundNormal);
          glTexCoord2f(0, 0);
          glVertex3f(m_cubeAspect, 0, m_cubeAspect);
          glTexCoord2f(1, 0);
          glVertex3f(m_cubeAspect, 0, 0);
          glTexCoord2f(0, 1);
          glVertex3f(0, 0, 0);
          glTexCoord2f(1, 1);
          glVertex3f(0, 0, m_cubeAspect);
        glEnd();
    glPopMatrix();

}

size_t Maze::getRows()
{
    return m_matrixRows;
}

size_t Maze::getCols()
{
    return m_matrixCols;
}

void Maze::draw()
{
    size_t i, j;

    glPushMatrix();

    for (i = 0; i < m_matrixRows; i++) {
        glPushMatrix();
        for (j = 0; j < m_matrixCols; j++) {
            if (index(i, j) == 1) drawWall();
            drawGround();
            glTranslatef(0, 0, m_cubeAspect);
        }
        glPopMatrix();

        glTranslatef(m_cubeAspect, 0, 0);
    }

    glPopMatrix();

    WorldObject::draw();
}

GLdouble Maze::indexX(size_t i, size_t j)
{
    return i * m_cubeAspect;
}

GLdouble Maze::indexY(size_t i, size_t j)
{
    return posY;
}

GLdouble Maze::indexZ(size_t i, size_t j)
{
    return j * m_cubeAspect;
}

void Maze::setAscpect(GLdouble a)
{
    m_cubeAspect = a;
}

void Maze::update() { }
