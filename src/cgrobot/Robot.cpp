#include "Robot.hpp"

using namespace cgrobot;

Robot::Robot(GLdouble x, GLdouble y, GLdouble z)
{
    posX = x, posY = y, posZ =z;

    quadric = gluNewQuadric();
    
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
}

void Robot::init()
{
}

Robot::~Robot()
{
    gluDeleteQuadric(quadric);
}

void Robot::turn(GLdouble dg)
{
    GLdouble rad = dg * M_PI / 180;

    posX = posX * cos(rad) - posY * sin(rad);
    posY = posX * sin(rad) + posY * cos(rad);
}

void Robot::drawEyes()
{
//CONSTRUÇÃO DOS OLHOS
	glPushMatrix();
		glRotatef(cabecaEixo, 0, 1, 0);
		//OLHO DIREITO
			//bronze - cilindro_menor / olho direito
			glPushMatrix();
				//glColor3f(0.56f, 0.48f, 0.332f);
				glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(olhoX, olhoY, 0);
				glTranslatef(0,0,-0.6);
				gluCylinder(quadric, 0.4f, 0.5f, 1.3, 50, 50);
			glPopMatrix();

			//bronze - cilindo_maior/ olho direito
			glPushMatrix();
				//glColor3f(0.56f, 0.48f, 0.332f);

				glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(olhoX, olhoY, 0.7);
				gluCylinder(quadric, 0.6f, 0.6f, 0.6, 50, 50);
			glPopMatrix();

			//branco - esclera / olho direito
			glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(olhoX, olhoY, 1.3);
				gluDisk(quadric, 0, 0.6f, 100, 100);
			glPopMatrix();

			//verde - iris / olho direito
			glPushMatrix();
				glColor3f((107/255.f), (142/255.f), (35/255.f));
				glTranslatef(olhoX, olhoY, 1.31);
				gluDisk(quadric, 0, 0.4f, 100, 100);
			glPopMatrix();

			//preto - pupila / olho direito
			glPushMatrix();
				glColor3f(0.f, 0.f, 0.f);
				glTranslatef(olhoX, olhoY, 1.311);
				gluDisk(quadric, 0, 0.2f, 100, 100);
			glPopMatrix();

		//OLHO ESQUERDO
			//bronze - cilindro_menor / olho esquerdo
			glPushMatrix();
				glColor3f((105/255.f), (105/255.f), (105/255.f));
				//glColor3f(0.56f, 0.48f, 0.332f);
				glTranslatef(-olhoX, olhoY, 0);
				glTranslatef(0,0,-0.6);
				gluCylinder(quadric, 0.4f, 0.5f, 1.3, 50, 50);
			glPopMatrix();

			//bronze - cilindo_maior/ olho esquerdo
			glPushMatrix();
				glColor3f((105/255.f), (105/255.f), (105/255.f));
				//glColor3f(0.56f, 0.48f, 0.332f);
				glTranslatef(-olhoX, olhoY, 0.7);
				gluCylinder(quadric, 0.6f, 0.6f, 0.6, 50, 50);
			glPopMatrix();

			//branco - esclera / olho esquerdo
			glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(-olhoX, olhoY, 1.3);
				gluDisk(quadric, 0, 0.6f, 100, 100);
			glPopMatrix();

			//verde - iris / olho esquerdo
			glPushMatrix();
				glColor3f((107/255.f), (142/255.f), (35/255.f));
				glTranslatef(-olhoX, olhoY, 1.31);
				gluDisk(quadric, 0, 0.4f, 100, 100);
			glPopMatrix();

			//preto - pupila / olho esquerdo
			glPushMatrix();
				glColor3f(0.f, 0.f, 0.f);
				glTranslatef(-olhoX, olhoY, 1.3111);
				gluDisk(quadric, 0, 0.2f, 100, 100);
			glPopMatrix();

		glPopMatrix();
}

void Robot::drawBody()
{
//CORPO
    //orange - body
    glPushMatrix();
      glColor3f(1, 0.5, 0);
      glutSolidCube(3);
    glPopMatrix();

		//ferrugens - body
		glPushMatrix();
			glColor3f ((112/255.f),(128/255.f), (144/255.f) );
			glTranslatef(1.1, 0.3, 0);
			glScalef(0.3, 0.2, 1);
			glutSolidCube(2.999);
		glPopMatrix();

		glPushMatrix();
			glColor3f ((112/255.f),(128/255.f), (144/255.f) );
			glTranslatef(-1.1, 0.3, 0);
			glScalef(0.3, 0.2, 1);
			glutSolidCube(2.999);
		glPopMatrix();

		glPushMatrix();
			glColor3f ((112/255.f),(128/255.f), (144/255.f) );
			glRotatef(90, 1, 0, 0);
			glRotatef(90, 0, 1, 0);
			glTranslatef(1.05, 1.25, 0);
			glScalef(0.3, 0.2, 1);
			glutSolidCube(2.999);
		glPopMatrix();

		glPushMatrix();
			glColor3f ((168/255.f),(168/255.f), (168/255.f) );
			glTranslatef(-1	, 1, 1.15);
			//glScalef(0.3, 0.2, 1);
			glutSolidCube(0.8);
		glPopMatrix();

		glPushMatrix();
			glColor3f ((217/255.f),(217/255.f), (25/255.f) );
			glTranslatef(-1.1, 1.1, 1.5);
			//glScalef(0.3, 0.2, 1);
			glutSolidCube(0.3);
		glPopMatrix();


		glPushMatrix();
			glColor3f (1,0,0 );
			glTranslatef(-0.2, 0.85, 1.5);
			//glScalef(0.3, 0.2, 1);
			glutSolidCube(0.3);
		glPopMatrix();


		glPushMatrix();
			glColor3f (0,0,1 );
			glTranslatef(0.5, 1.2, 1.5);
			//glScalef(0.3, 0.2, 1);
			glutSolidCube(0.3);
		glPopMatrix();

		glPushMatrix();
			glColor3f (1,0,1 );
			glTranslatef(1, 0.85, 1.5);
			//glScalef(0.3, 0.2, 1);
			glutSolidCube(0.3);
		glPopMatrix();
}

void Robot::drawArms()
{
//CONSTRUÇÃO DOS BRAÇOS

    //color - arm1
    glPushMatrix();
        // glColor3f(0.56f, 0.48f, 0.332f);
				glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(-1.7, 0.3, 0.7);
				glRotatef(45, 1, 0, 0);
				glRotatef(arm, 1, 0, 0);
				glTranslatef(0, 1.1, 0);
        glScalef(0.7,2.5,0.7);
        glutSolidCube(1);
    glPopMatrix();

    //color - arm2
    glPushMatrix();
				// glColor3f(0.56f, 0.48f, 0.332f);
				glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(1.7, 0.3, 0.7);
				glRotatef(45, 1, 0, 0);
				glRotatef(arm, 1, 0, 0);
				glTranslatef(0, 1.1, 0);
				glScalef(0.7,2.5,0.7);
        glutSolidCube(1);
    glPopMatrix();
}

void Robot::drawNeck()
{
//CONSTRUÇÃO DO PESCOÇO

		//bronze / parte1/ base - pescoço
		glPushMatrix();
			// glColor3f(0.56f, 0.48f, 0.332f);
			glColor3f((105/255.f), (105/255.f), (105/255.f));
			glTranslatef(0,2,0.3);
			glRotatef(90, 1, 0, 0);
			glRotatef(60, 1,0,0);
			gluCylinder(quadric, 0.3f, 0.3f, 1.5, 30, 30);
		glPopMatrix();

		//bronze / parte2/ centro - pescoço
		glPushMatrix();
			//glColor3f(0.56f, 0.48f, 0.332f);

			glColor3f((105/255.f), (105/255.f), (105/255.f));
			glTranslatef(-0.3,2,0.1);
			glRotatef(90, 1, 0, 0);
			glRotatef(90, 0, 1, 0);
			gluCylinder(quadric, 0.3f, 0.3f, 0.6f, 50, 50);
		glPopMatrix();

		//bronze /parte3/ superior - pescoço
		glPushMatrix();
			// glColor3f(0.56f, 0.48f, 0.332f);
			glColor3f((105/255.f), (105/255.f), (105/255.f));
			glTranslatef(0,2.5,0.2);
			glRotatef(90, 1, 0, 0);
			//glRotatef(60, 1,0,0);
			gluCylinder(quadric, 0.3f, 0.3f, 0.7, 50, 50);
		glPopMatrix();
}

void Robot::drawWheels()
{
//CONSTRUÇÃO DAS RODAS
			//cinza - esteira das rodas1
			glPushMatrix();
				glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(-2.3, -1.8, 0);
				glRotatef(90, 0, 1, 0);
				glScalef (1.3,0.8,1.3);
				gluCylinder(quadric, 1.7f, 1.7f, 1.f, 3, 3);
			glPopMatrix();

			//tampa esteira 1
			glPushMatrix();
				glColor3f((139/255.f), (69/255.f), (19/255.f));
				glTranslatef(-1.7, -1.8, 0);
				glRotatef(90, 0, 1, 0);
				glScalef (1.3,0.8,1.3);
				gluDisk(quadric, 0.f, 1.7f, 3, 3);
			glPopMatrix();

			glPushMatrix(); //RODA 1 ESQUERDA
		        glPushMatrix(); //marrom - roda grande
		            glColor3f(0.368f, 0.204f, 0.092f);
                    glTranslatef(-2,-1.9, 0.545);
		            glRotatef(90,1,0,0);
		            glRotatef(90,0,1,0);
		            glutSolidTorus(0.1,0.5,100,100);
		        glPopMatrix();

				glPushMatrix();	//bronze / aro roda
					glColor3f(0.368f, 0.204f, 0.092f);
					//glColor3f((105/255.f), (105/255.f), (105/255.f));
					glTranslatef(-2,-1.85, 0.5);
					glRotatef(90, 1,0,0);
					glRotatef(rotateEixo, 1,0,0);
					glTranslatef(0, 0.5,0);
					glRotatef(90, 1, 0, 0);
					gluCylinder(quadric, 0.05f, 0.05f, 1, 30, 30);
				glPopMatrix();

				glPushMatrix(); //bronze / aro2 roda
					glColor3f(0.368f, 0.204f, 0.092f);
					//glColor3f((105/255.f), (105/255.f), (105/255.f));
					glTranslatef(-2,-1.85, 0.45);
					glRotatef(rotateEixo, 1,0,0);
					glTranslatef(0, 0.5,0);
					glRotatef(90, 1, 0, 0);
					gluCylinder(quadric, 0.05f, 0.05f, 1, 30, 30);
				glPopMatrix();
			glPopMatrix(); //ENCERRA RODA 1

			
			glPopMatrix(); //RODA 2 ESQUERDA
				glPushMatrix();	//marrom- roda menor inferior
						glColor3f(0.368f, 0.204f, 0.092f);
						glTranslatef(-2,-2.1, -0.95);
						glRotatef(90,1,0,0);
						glRotatef(90,0,1,0);
						glutSolidTorus(0.1,0.3,100,100);
				glPopMatrix();

				//bronze / aro roda
				glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					//glColor3f((105/255.f), (105/255.f), (105/255.f));
					glTranslatef(-2.,-2.1, -0.95);
					glRotatef(90, 1,0,0);
					glRotatef(-rotateEixo, 1,0,0);
					glTranslatef(0, 0.2,0);
					glRotatef(90, 1, 0, 0);
					gluCylinder(quadric, 0.05f, 0.05f, 0.55, 30, 30);
				glPopMatrix();

				//bronze / aro2 roda
				glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					//glColor3f((105/255.f), (105/255.f), (105/255.f));
					glTranslatef(-2.,-2.1, -0.9);
					glRotatef(-rotateEixo, 1,0,0);
					glTranslatef(0, 0.3,0);
					glRotatef(90, 1, 0, 0);
					//glRotatef(-30, 1,0,0);
					gluCylinder(quadric, 0.05f, 0.05f, 0.55, 30, 30);
				glPopMatrix();
			glPopMatrix(); //ENCERRA RODA 2


			glPushMatrix(); //RODA 3 ESQUERDA
				//marrom- roda
				glPushMatrix();
						glColor3f(0.368f, 0.204f, 0.092f);
						glTranslatef(-2,-1.5, -0.37);
						glRotatef(90,1,0,0);
						glRotatef(90,0,1,0);
						glutSolidTorus(0.1,0.35,100,100);
				glPopMatrix();

				//bronze / aro roda
				glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					//glColor3f((105/255.f), (105/255.f), (105/255.f));
					glTranslatef(-2.,-1.55, -0.35);
					glRotatef(90, 1,0,0);

					glRotatef(rotateEixo, 1,0,0);
					glTranslatef(0, 0.3,0);
					glRotatef(90, 1, 0, 0);
					gluCylinder(quadric, 0.05f, 0.05f, 0.6, 30, 30);
				glPopMatrix();

				//bronze / aro2 roda
				glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					//glColor3f((105/255.f), (105/255.f), (105/255.f));
					glTranslatef(-2.,-1.5, -0.35);
					glRotatef(rotateEixo, 1,0,0);
					glTranslatef(0, 0.3,0);
					glRotatef(90, 1, 0, 0);
					//glRotatef(-30, 1,0,0);
					gluCylinder(quadric, 0.05f, 0.05f, 0.65, 30, 30);
				glPopMatrix();
		    glPopMatrix(); //ENCERRA RODA 3


		    glPushMatrix(); //RODA 4 ESQUERDA
				//marrom- roda
				glPushMatrix();
						glColor3f(0.368f, 0.204f, 0.092f);
						glTranslatef(-2,-1.2, 0.24);
						glRotatef(90,1,0,0);
						glRotatef(90,0,1,0);
						glutSolidTorus(0.07,0.25,100,100);
				glPopMatrix();

				//bronze / aro roda
				glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					//glColor3f((105/255.f), (105/255.f), (105/255.f));
					glTranslatef(-2.,-1.2, 0.25);
					glRotatef(90, 1,0,0);
					glRotatef(-rotateEixo, 1,0,0);
					glTranslatef(0, 0.2,0);
					glRotatef(90, 1, 0, 0);
					gluCylinder(quadric, 0.05f, 0.05f, 0.4, 30, 30);
				glPopMatrix();

				//bronze / aro2 roda
				glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					//glColor3f((105/255.f), (105/255.f), (105/255.f));
					glTranslatef(-2.,-1.2, 0.25);
					glRotatef(-rotateEixo, 1,0,0);
					glTranslatef(0, 0.2,0);
					glRotatef(90, 1, 0, 0);
					gluCylinder(quadric, 0.05f, 0.05f, 0.4, 30, 30);
				glPopMatrix();
		    glPopMatrix(); //ENCERRA RODA 4


		//cinza - esteira das rodas2
		glPushMatrix();
			glColor3f((105/255.f), (105/255.f), (105/255.f));
			glTranslatef(1, -1.8, 0);
			glRotatef(90, 0, 1, 0);
			glScalef (1.3,0.8,1.3);
			gluCylinder(quadric, 1.7f, 1.7f, 1.f, 3, 3);
		glPopMatrix();

		//tampa esteira 1
		glPushMatrix();
			glColor3f((139/255.f), (69/255.f), (19/255.f));
			glTranslatef(1.7, -1.8, 0);
			glRotatef(90, 0, 1, 0);
			glScalef (1.3,0.8,1.3);
			gluDisk(quadric, 0.f, 1.7f, 3, 3);
		glPopMatrix();

		//RODA 1 ESQUERDA
		glPushMatrix();
			//marrom - roda grande
			glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					glTranslatef(2,-1.9, 0.545);
					glRotatef(90,1,0,0);
					glRotatef(90,0,1,0);
					glutSolidTorus(0.1,0.5,100,100);
			glPopMatrix();

			//bronze / aro roda
			glPushMatrix();
				glColor3f(0.368f, 0.204f, 0.092f);
				//glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(2,-1.85, 0.5);
				glRotatef(90, 1,0,0);
				glRotatef(rotateEixo, 1,0,0);
				glTranslatef(0, 0.5,0);
				glRotatef(90, 1, 0, 0);
				gluCylinder(quadric, 0.05f, 0.05f, 1, 30, 30);
			glPopMatrix();

			//bronze / aro2 roda
			glPushMatrix();
				glColor3f(0.368f, 0.204f, 0.092f);
				//glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(2,-1.85, 0.45);
				glRotatef(rotateEixo, 1,0,0);
				glTranslatef(0, 0.5,0);
				glRotatef(90, 1, 0, 0);
				gluCylinder(quadric, 0.05f, 0.05f, 1, 30, 30);
			glPopMatrix();

		//ENCERRA RODA 1
		glPopMatrix();

		//RODA 2 ESQUERDA
		glPopMatrix();
			//marrom- roda menor inferior
			glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					glTranslatef(2,-2.1, -0.95);
					glRotatef(90,1,0,0);
					glRotatef(90,0,1,0);
					glutSolidTorus(0.1,0.3,100,100);
			glPopMatrix();

			//bronze / aro roda
			glPushMatrix();
				glColor3f(0.368f, 0.204f, 0.092f);
				//glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(2.,-2.1, -0.95);
				glRotatef(90, 1,0,0);
				glRotatef(-rotateEixo, 1,0,0);
				glTranslatef(0, 0.2,0);
				glRotatef(90, 1, 0, 0);
				gluCylinder(quadric, 0.05f, 0.05f, 0.55, 30, 30);
			glPopMatrix();

			//bronze / aro2 roda
			glPushMatrix();
				glColor3f(0.368f, 0.204f, 0.092f);
				//glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(2.,-2.1, -0.9);
				glRotatef(-rotateEixo, 1,0,0);
				glTranslatef(0, 0.3,0);
				glRotatef(90, 1, 0, 0);
				//glRotatef(-30, 1,0,0);
				gluCylinder(quadric, 0.05f, 0.05f, 0.55, 30, 30);
			glPopMatrix();

		//ENCERRA RODA 2
		glPopMatrix();


		//RODA 3 ESQUERDA
		glPushMatrix();

			//marrom- roda
			glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					glTranslatef(2,-1.5, -0.37);
					glRotatef(90,1,0,0);
					glRotatef(90,0,1,0);
					glutSolidTorus(0.1,0.35,100,100);
			glPopMatrix();

			//bronze / aro roda
			glPushMatrix();
				glColor3f(0.368f, 0.204f, 0.092f);
				//glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(2.,-1.55, -0.35);
				glRotatef(90, 1,0,0);

				glRotatef(rotateEixo, 1,0,0);
				glTranslatef(0, 0.3,0);
				glRotatef(90, 1, 0, 0);
				gluCylinder(quadric, 0.05f, 0.05f, 0.6, 30, 30);
			glPopMatrix();

			//bronze / aro2 roda
			glPushMatrix();
				glColor3f(0.368f, 0.204f, 0.092f);
				//glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(2.,-1.5, -0.35);
				glRotatef(rotateEixo, 1,0,0);
				glTranslatef(0, 0.3,0);
				glRotatef(90, 1, 0, 0);
				//glRotatef(-30, 1,0,0);
				gluCylinder(quadric, 0.05f, 0.05f, 0.65, 30, 30);
			glPopMatrix();

	//ENCERRA RODA 3
	glPopMatrix();

	//RODA 4 ESQUERDA
	glPushMatrix();
			//marrom- roda
			glPushMatrix();
					glColor3f(0.368f, 0.204f, 0.092f);
					glTranslatef(2,-1.2, 0.24);
					glRotatef(90,1,0,0);
					glRotatef(90,0,1,0);
					glutSolidTorus(0.07,0.25,100,100);
			glPopMatrix();

			//bronze / aro roda
			glPushMatrix();
				glColor3f(0.368f, 0.204f, 0.092f);
				//glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(2.,-1.2, 0.25);
				glRotatef(90, 1,0,0);
				glRotatef(-rotateEixo, 1,0,0);
				glTranslatef(0, 0.2,0);
				glRotatef(90, 1, 0, 0);
				gluCylinder(quadric, 0.05f, 0.05f, 0.4, 30, 30);
			glPopMatrix();

			//bronze / aro2 roda
			glPushMatrix();
				glColor3f(0.368f, 0.204f, 0.092f);
				//glColor3f((105/255.f), (105/255.f), (105/255.f));
				glTranslatef(2.,-1.2, 0.25);
				glRotatef(-rotateEixo, 1,0,0);
				glTranslatef(0, 0.2,0);
				glRotatef(90, 1, 0, 0);
				gluCylinder(quadric, 0.05f, 0.05f, 0.4, 30, 30);
			glPopMatrix();
	//ENCERRA RODA 4
	glPopMatrix();
}

void Robot::draw()
{
    GLfloat  specular[4] = { .5, .5, .5, 1.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, specular);

    glPushMatrix();
      WorldObject::draw();
      glTranslatef(0, 3.5, 0);

      glPushMatrix();
        drawBody();
        drawArms();
        drawNeck();
        drawEyes();
        drawWheels();
      glPopMatrix();
    glPopMatrix();
}

void Robot::update()
{
    rotateEixo += 1;
}
