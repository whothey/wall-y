#include "Plant.hpp"

using namespace cgrobot;

Plant::Plant(GLdouble x, GLdouble y, GLdouble z)
{
    posX = x, posY = y, posZ =z;

    quadric = gluNewQuadric();

    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
}

void Plant::init()
{
}

Plant::~Plant()
{
    gluDeleteQuadric(quadric);
}

<<<<<<< HEAD
void Plant::turn(GLdouble dg)
{
    GLdouble rad = dg * M_PI / 180;

    posX = posX * cos(rad) - posY * sin(rad);
    posY = posX * sin(rad) + posY * cos(rad);
}

=======
>>>>>>> 93164c3ea2a9097a42349864af42395ccb8fb52c
void Plant::drawGreen()
{
  //PLANTA
  		//CAULE
  		glPushMatrix();
  			glColor3f((107/255.f), (142/255.f), (35/255.f));
  			glTranslatef(-1.9,5,0);
  			glScalef(0.5,6.3,0.5);
  			glutSolidCube(1);
  		glPopMatrix();

  		//folha1
  		glPushMatrix();
  			glColor3f((107/255.f), (142/255.f), (35/255.f));
        glTranslatef(-1.5, 7,0);
  			gluSphere(quadric, 0.5f, 100, 100);
  		glPopMatrix();

  		glPushMatrix();
  			glColor3f((107/255.f), (142/255.f), (35/255.f));
  			glTranslatef(-1.2, 6.7,0);
  			glRotatef(15, 0, 0, 1);
  			glScalef(3, 1, 1 );
  			glutSolidCube(0.5);
  		glPopMatrix();

  		glPushMatrix();
  			glColor3f((107/255.f), (142/255.f), (35/255.f));
  			glTranslatef(-1.2, 7.1,0);
  			glRotatef(-15, 0, 0, 1);
  			glScalef(3, 1, 1 );
  			glutSolidCube(0.5);
  		glPopMatrix();

  		//folha2
  		glPushMatrix();

  					glPushMatrix();
  						glColor3f((107/255.f), (142/255.f), (35/255.f));
  						glTranslatef(-2.3, 6,0);
  						gluSphere(quadric, 0.5f, 100, 100);
  					glPopMatrix();

  					glPushMatrix();
  						glColor3f((107/255.f), (142/255.f), (35/255.f));
  						glTranslatef(-2.4, 6.3,0);
  						glRotatef(15, 0, 0, 1);
  						glScalef(3, 1, 1 );
  						glutSolidCube(0.5);
  					glPopMatrix();

  					glPushMatrix();
  						glColor3f((107/255.f), (142/255.f), (35/255.f));
  						glTranslatef(-2.4, 5.8,0);
  						glRotatef(-15, 0, 0, 1);
  						glScalef(3, 1, 1 );
  						glutSolidCube(0.5);
  					glPopMatrix();
  			glPopMatrix();
}

void Plant::drawBoot()
{
  //BOTA
  glPushMatrix();
    glColor3f((139/255.f), (69/255.f), (19/255.f));
    glTranslatef(2.9,-0.1,0);
    gluSphere(quadric, 2.f, 100, 100);
  glPopMatrix();

  glPushMatrix();
    glColor3f((139/255.f), (69/255.f), (19/255.f));
    glTranslatef(0,0.2,0);
    glScalef(2,1.1,1);
    glutSolidCube(3);
  glPopMatrix();

  glPushMatrix();
    glColor3f((139/255.f), (69/255.f), (19/255.f));
    glTranslatef(-1.9,-0.5,0);
    glutSolidCube(3);
  glPopMatrix();

  glPushMatrix();
    glColor3f((139/255.f), (69/255.f), (19/255.f));
    glRotatef(15, 0, 0, -1);
    glTranslatef(2,-0.1,0);
    glScalef(1.,0.7,1);
    glutSolidCube(3);
  glPopMatrix();

  glPushMatrix();
    glColor3f((139/255.f), (69/255.f), (19/255.f));
    glTranslatef(-1.9,2,0);
    glScalef(1.,1.4,1);
    glutSolidCube(3);
  glPopMatrix();

}


void Plant::draw()
{
    GLfloat  specular[4] = { .5, .5, .5, 1.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, specular);
    glPushMatrix();
    glDisable(GL_LIGHTING);

      WorldObject::draw();
      glTranslatef(0, 3.5, 0);
      glPushMatrix();
        glScalef(0.3,0.3,0.3);
        drawGreen();
        drawBoot();
      glPopMatrix();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Plant::update()
{
<<<<<<< HEAD
    rotateEixo += 1;
=======
>>>>>>> 93164c3ea2a9097a42349864af42395ccb8fb52c
}
