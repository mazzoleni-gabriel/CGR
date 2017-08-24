// gcc castelo.cpp -lglut -lGL -lGLU -o  castelo && ./castelo
#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define NUM_PARTICLES 3000
#define GRAVITY 0.0003


float angle = 0.0;
GLUquadric* qobj;


static void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   gluLookAt(0.0, 6.5, 4.0,
             0.0, 0.0, 1.0,
             0.0, 0.0, 1.0);

   angle += 0.05;

   glRotated(angle, 0, 0, 1);
   glColor3f(0.3, 0.05, 0.0);
	
	//Porta
   glPushMatrix();
      glTranslatef(0.0, 0.0, 0.0);
      gluCylinder(qobj, 0.4, 0.4, 1, 4, 2);
   glPopMatrix();  
   
   //Torre 1
   glPushMatrix();
      glTranslatef(2.0, 0.0, 0.0);
      gluCylinder(qobj, 0.4, 0.4, 1.2, 32, 32);
   glPopMatrix();

   //Torre 2
   glPushMatrix();
      glTranslatef(2.0, -4.0, 0.0);
      gluCylinder(qobj, 0.4, 0.4, 1.2, 32, 32);
   glPopMatrix();
   
   //Torre 3
   glPushMatrix();
      glTranslatef(-2.0, 0.0, 0.0);
      gluCylinder(qobj, 0.4, 0.4, 1.2, 32, 32);
   glPopMatrix();
     
    //Torre 4
   glPushMatrix();
      glTranslatef(-2.0, -4.0, 0.0);
      gluCylinder(qobj, 0.4, 0.4, 1.2, 32, 32);
   glPopMatrix();

   //Torre do meio
   glPushMatrix();
      glTranslatef(-0.5, -3.0, 0.0);
      gluCylinder(qobj, 0.5, 0.5, 2, 4, 2);
   glPopMatrix();
 
   //Parede frente
   glBegin(GL_POLYGON);
	  glVertex3f(  2.0, 0.0, 0.9 );
	  glVertex3f(  2.0, 0.0, 0.0 );
	  glVertex3f( -2.0, 0.0, 0.0 );
   	  glVertex3f( -2.0, 0.0, 0.9);
   glEnd();
   
   
   //Parede Esquerda
   glBegin(GL_POLYGON);
	  glVertex3f(  2.0, 0.0, 0.9 );
	  glVertex3f(  2.0, 0.0, 0.0 );
	  glVertex3f(  2.0, -4.0, 0.0 );
   	  glVertex3f(  2.0, -4.0, 0.9);
   glEnd();
   
   //Parede Direita
   glBegin(GL_POLYGON);
	  glVertex3f( -2.0, 0.0, 0.9 );
	  glVertex3f( -2.0, 0.0, 0.0 );
	  glVertex3f( -2.0, -4.0, 0.0 );
   	  glVertex3f( -2.0, -4.0, 0.9);
   glEnd();
   
   //Parede trás
   glBegin(GL_POLYGON);
	  glVertex3f(  2.0, -4.0, 0.9 );
	  glVertex3f(  2.0, -4.0, 0.0 );
	  glVertex3f( -2.0, -4.0, 0.0 );
   	  glVertex3f( -2.0, -4.0, 0.9);
   glEnd();
   
   glColor3f(0.1, 0.0, 0.0);
   
   //Teto Entrada
	glPushMatrix();
      glTranslatef(0.0, 0.0, 0.95);
      gluCylinder(qobj, 0.45, 0, 0.55, 4, 32);
   glPopMatrix();
   
   //Teto 1
   glPushMatrix();
      glTranslatef(2.0, 0.0, 1.15);
      gluCylinder(qobj, 0.45, 0.0, 0.65, 32, 5);
   glPopMatrix();
   
   //Teto 2
   glPushMatrix();
      glTranslatef(2.0, -4.0, 1.15);
      gluCylinder(qobj, 0.45, 0.0, 0.65, 32, 5);
   glPopMatrix();
   
   //Teto 3
   glPushMatrix();
      glTranslatef(-2.0, 0.0, 1.15);
      gluCylinder(qobj, 0.45, 0.0, 0.65, 32, 5);
   glPopMatrix();
   
   //Teto 4
   glPushMatrix();
      glTranslatef(-2.0, -4.0, 1.15);
      gluCylinder(qobj, 0.45, 0.0, 0.65, 32, 5);
   glPopMatrix();
   
   //Teto Torre do meio
   glPushMatrix();
      glTranslatef(-0.5, -3.0, 1.95);
      gluCylinder(qobj, 0.57, 0, 0.5, 4, 2);
   glPopMatrix();
   
   
   
   glColor3f(0.3, 0.3, 0.3);
   //Chão  
   glBegin(GL_POLYGON);
	  glVertex3f(  2.5, -4.5, 0.0 );
	  glVertex3f(  2.5,  0.5, 0.0 );
	  glVertex3f( -2.5,  0.5, 0.0 );
   	  glVertex3f( -2.5, -4.5, 0.0 );
   glEnd();
	
   

   //void glutSolidCone(GLdouble base, GLdouble height,GLint slices, GLint stacks);
   
   glFlush();
   glutSwapBuffers();
}

int main (int argc, char **argv)
{
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	
	
		
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(800,600);
    glutCreateWindow("Castelo");

    glutDisplayFunc(display);
    glutIdleFunc( display );

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = (GLfloat) 800 / 600;
    gluPerspective(45, aspect, 2.0f, 15.0f);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glClearColor(0.0, 0.0, 0.0, 1.0);

    GLfloat mat_shininess[] =  { 50.0 };
    GLfloat mat_specular[] =   { 0.75, 0.75, 0.75, 0.75 };

    GLfloat light_ambient[] =  {  1.0,  1.0,  1.0, 1.0 };
    GLfloat light_diffuse[] =  {  1.0,  1.0,  1.0, 1.0 };
    GLfloat light_specular[] = {  1.0,  1.0,  1.0, 1.0 };
    GLfloat light_position[] = {  10.0,  2.0,  10.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glutMainLoop();
    gluDeleteQuadric(qobj);
    

    return 0;
}
