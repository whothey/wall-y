#include "Lighter.hpp"

using namespace cgrobot;

Lighter::Lighter(GLdouble x, GLdouble y, GLdouble z)
{
    posX = x, posY = y, posZ =z;

    quadric = gluNewQuadric();

    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
}

void Lighter::init()
{ }

Lighter::~Lighter()
{
    gluDeleteQuadric(quadric);
}

void Lighter::drawLighter()
{
  //corpo isqueiro
  glPushMatrix();
    glColor3f((128/255.f), (128/255.f), (128/255.f));
    glTranslatef(0,0,0);
    glScalef(1.7,2.2,1);
    glutSolidCube(3);
  glPopMatrix();

  //tampa isqueiro
    glPushMatrix();
      glColor3f((128/255.f), (128/255.f), (128/255.f));
      glTranslatef(3,5.3,0);
      glScalef(0.5,1.7,1);
      glutSolidCube(3);
    glPopMatrix();

  //fivelas tampa
  glPushMatrix();
    glColor3f((105/255.f),(105/255.f),(105/255.f));
    glTranslatef(2.2,2.9,1.3);
    gluSphere(quadric, 0.4f, 100, 100);
  glPopMatrix();

  glPushMatrix();
    glColor3f((105/255.f),(105/255.f),(105/255.f));
    glTranslatef(2.2,2.9,-1.3);
    gluSphere(quadric, 0.4f, 100, 100);
  glPopMatrix();

  //esfera central
  glPushMatrix();
    glColor3f((105/255.f),(105/255.f),(105/255.f));
    glTranslatef(-0.5,3.3,0);
    gluCylinder(quadric, 0.8f, 1.3f, 0.1, 30, 30);
  glPopMatrix();

  glPushMatrix();
      glColor3f((105/255.f),(105/255.f),(105/255.f));
      glTranslatef(-0.5,3.3,0.1);
      gluCylinder(quadric, 0.8f, 1.3f, 0.1, 30, 30);
  glPopMatrix();

  glPushMatrix();
    glColor3f((105/255.f),(105/255.f),(105/255.f));
    glTranslatef(-0.5,3.3,-0.1);
    gluCylinder(quadric, 0.8f, 1.3f, 0.1, 30, 30);
  glPopMatrix();

//esfera menor
  glPushMatrix();
    glColor3f((105/255.f),(105/255.f),(105/255.f));
    glTranslatef(1.2,3.3,0);
    gluCylinder(quadric, 0.4f, 0.8f, 0.1, 30, 30);
  glPopMatrix();

//desenho centro
glPushMatrix();
  glColor3f(1,(99/255.f),(71/255.f));
  glTranslatef(0,0,1.5);
  gluCylinder(quadric, 0.0f, 1.5f, 0.1, 100, 100);
glPopMatrix();

glPushMatrix();
  glColor3f((192/255.f), (192/255.f), (192/255.f));
  glTranslatef(0,-0.4,1.6);
  gluCylinder(quadric, 0.1f, 0.3f, 0.1, 100, 100);
glPopMatrix();

}


void Lighter::draw()
{
    GLfloat  specular[4] = { .5, .5, .5, 1.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, specular);
    glPushMatrix();
    glDisable(GL_LIGHTING);

      WorldObject::draw();
      glTranslatef(0, 3.5, 0);
      glPushMatrix();
        glScalef(0.3,0.3,0.3);
        drawLighter();
      glPopMatrix();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Lighter::update() {}
