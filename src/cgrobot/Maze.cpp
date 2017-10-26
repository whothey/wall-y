#include "Maze.hpp"
#include <iostream>

using namespace cgrobot;

Maze::Maze() : m_cubeHeight(10), m_cubeAspect(5) {};

Maze::Maze(GLint *adjMatrix, size_t nrows, size_t ncols)
    : m_matrix(adjMatrix), m_matrixRows(nrows), m_matrixCols(ncols)
    , m_cubeHeight(10), m_cubeAspect(5)
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
    GLfloat  specular[4] = { 1.0, 1.0, 1.0, 1.0 };

    glColor3f(0, 1, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, specular);

    GLdouble vertexs[8][3] = {
        { center[0] + size, center[1] + size, center[2] - size },  // A - 0
        { center[0] + size, center[1] + size, center[2] + size },  // B - 1
        { center[0] + size, center[1] - size, center[2] + size },  // C - 2
        { center[0] + size, center[1] - size, center[2] - size },  // D - 3
        { center[0] - size, center[1] + size, center[2] + size },  // E - 4
        { center[0] - size, center[1] - size, center[2] + size },  // F - 5
        { center[0] - size, center[1] + size, center[2] - size },  // G - 6
        { center[0] - size, center[1] - size, center[2] - size },  // H - 7
    };

    // Back
    glBegin(GL_QUADS);

    glBindTexture(GL_TEXTURE_2D, m_wallTexture);

    // Right
    glTexCoord2f(0, 0);       glVertex3dv(vertexs[0]);
    glTexCoord2f(2.0f, 0);    glVertex3dv(vertexs[3]);
    glTexCoord2f(0, 2.0f);    glVertex3dv(vertexs[2]);
    glTexCoord2f(2.0f, 2.0f); glVertex3dv(vertexs[1]);

    // Back
    glTexCoord2f(0, 0);       glVertex3dv(vertexs[1]);
    glTexCoord2f(2.0f, 0);    glVertex3dv(vertexs[2]);
    glTexCoord2f(0, 2.0f);    glVertex3dv(vertexs[5]);
    glTexCoord2f(2.0f, 2.0f); glVertex3dv(vertexs[4]);

    // Top
    glTexCoord2f(0, 0);       glVertex3dv(vertexs[6]);
    glTexCoord2f(2.0f, 0);    glVertex3dv(vertexs[0]);
    glTexCoord2f(0, 2.0f);    glVertex3dv(vertexs[1]);
    glTexCoord2f(2.0f, 2.0f); glVertex3dv(vertexs[4]);

    // Left
    glTexCoord2f(0, 0);       glVertex3dv(vertexs[6]);
    glTexCoord2f(2.0f, 0);    glVertex3dv(vertexs[7]);
    glTexCoord2f(0, 2.0f);    glVertex3dv(vertexs[5]);
    glTexCoord2f(2.0f, 2.0f); glVertex3dv(vertexs[4]);

    // Front
    glTexCoord2f(0, 0);       glVertex3dv(vertexs[6]);
    glTexCoord2f(2.0f, 0);    glVertex3dv(vertexs[7]);
    glTexCoord2f(0, 2.0f);    glVertex3dv(vertexs[3]);
    glTexCoord2f(2.0f, 2.0f); glVertex3dv(vertexs[0]);

    // Bottom
    glTexCoord2f(0, 0);       glVertex3dv(vertexs[3]);
    glTexCoord2f(2.0f, 0);    glVertex3dv(vertexs[2]);
    glTexCoord2f(0, 2.0f);    glVertex3dv(vertexs[5]);
    glTexCoord2f(2.0f, 2.0f); glVertex3dv(vertexs[7]);

    glEnd();
}

void Maze::draw()
{
    size_t i, j;
    GLfloat
        groundStart  = -m_cubeAspect / 2,
        groundWidth  = (m_matrixCols) * m_cubeAspect,
        groundHeight = (m_matrixRows) * m_cubeAspect;

    glPushMatrix();

    glColor3f(213/255.0f, 208/255.0f, 178/255.0f);

    glBindTexture(GL_TEXTURE_2D, m_groundTexture);
    glBegin(GL_QUADS);
      // Chão
      glTexCoord2f(0, 0);
      glVertex3f(groundStart, 0, groundStart);
      glTexCoord2f(4.0f, 0);
      glVertex3f(groundHeight, 0, groundStart);
      glTexCoord2f(0, 4.0f);
      glVertex3f(groundHeight, 0, groundWidth);
      glTexCoord2f(4.0f, 4.0f);
      glVertex3f(groundStart, 0, groundWidth);
    glEnd();

    glColor3f(0, 1, 0);

    glBindTexture(GL_TEXTURE_2D, m_wallTexture);

    glTranslatef(0, m_cubeAspect / 2, 0);

    for (i = 0; i < m_matrixRows; i++) {
        glPushMatrix();
        for (j = 0; j < m_matrixCols; j++) {
            if (index(i, j) == 1) drawWall();
            glTranslatef(0, 0, m_cubeAspect);
        }
        glPopMatrix();

        glTranslatef(m_cubeAspect, 0, 0);
    }

    glPopMatrix();

    WorldObject::draw();
}

void Maze::update() { }
