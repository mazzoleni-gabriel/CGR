// gcc robo.cpp -lglut -lGL -lGLU -o  robo && ./robo
// g++ robo.cpp -lglut -lGL -lGLU -o  robo && ./robo
#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <unistd.h>


#define NUM_PARTICLES 3000
#define g 0.00008
#define pi 3.14159265358979323846


#define ESCAPE 27
#define FRENTE 119
#define TRAS 115
#define ESQ 97
#define DIR 100

float angle = 0.0;
GLUquadric* qobj;


struct parte {
	float x,y,z; //coordenadas xyz
	float bot,top,h; //raio da base, raio do topo e altura
	float r1,r2,r3,r4; 
};
struct parte pernaEsq, pernaDir, tronco, tampatronco, pescoco, cabeca, braco1, braco2, luva1, luva2;
struct parte pe1, pe2, chapeu, olho1, olho2, tampaolho1, tampaolho2;
int andaDir = 1, andaEsq=-1;

//pulo
int pulo=0;
float a,v = 0.02,t = 0,v0 = 0.02; 
//Andar
float vel_andar = 0.05, angulo_andar = 30;
// rot camera
float rot = 0.0;


void initRobo(){ // Função que inicia as coordenadas das partes do robo
	//tronco
	tronco.bot = 0.7;
	tronco.top = 0.7;
	tronco.h = 1.2;
	tronco.x=0;
	tronco.y=0;
	tronco.z=1.2;;
	
	//perna direita
	pernaDir.r3 = 1;
	
	//perna esquerda
	pernaEsq.r3 = 1;
	
	
}

int graurad(float grau){
	return grau*0.0174533;
}

void attRobo(){ // Função que inicia as coordenadas das partes do robo
	
	//perna esquerda
	pernaEsq.bot = tronco.bot/4;
	pernaEsq.top =  pernaEsq.bot;
	pernaEsq.h =  tronco.h;
	pernaEsq.x = tronco.x;
	pernaEsq.y = tronco.y-0.5;
	pernaEsq.z = tronco.z;
	
	
	//perna direita
	pernaDir.bot = pernaEsq.bot;
	pernaDir.top = pernaDir.bot;
	pernaDir.h = pernaEsq.h;
	pernaDir.x = tronco.x;
	pernaDir.y = tronco.y + 0.5;
	pernaDir.z = tronco.z;
	
	
	//tampatronco
	tampatronco.bot = tronco.bot;
	tampatronco.top = 0;
	tampatronco.h = 0;
	tampatronco.x=tronco.x;
	tampatronco.y=tronco.y;
	tampatronco.z=tronco.z + tronco.h;
	
	//pescoco
	pescoco.bot = tronco.h/6;
	pescoco.top =  pescoco.bot;
	pescoco.h = tronco.h/5;
	pescoco.x=tronco.x;
	pescoco.y=tronco.y;
	pescoco.z=tronco.z + tronco.h;
	
	//cabeca
	cabeca.bot = tronco.bot/1.9;
	cabeca.top =  cabeca.bot;
	cabeca.h =  0.5;
	cabeca.x=tronco.x;
	cabeca.y=tronco.y;
	cabeca.z=pescoco.z + pescoco.h;
	
	//braço1
	braco1.r1 = 90;
	braco1.r2 = -1;
	braco2.r3 = 0; 
	braco2.r4 = 0;
	braco1.bot = pernaDir.bot;
	braco1.top = pernaDir.top;
	braco1.h = pernaDir.h;
	braco1.x = tronco.x;
	braco1.y = tronco.bot + tronco.y;
	braco1.z = tronco.z + tronco.h/1.5;

	
	//braço2
	braco2.r1 = 0; //cima baixo
	braco2.r2 = 0;  //x
	braco2.r3 = 0; //y
	braco2.r4 = 0; //z
	braco2.bot = pernaDir.bot;
	braco2.top = pernaDir.top;
	braco2.h = pernaDir.h;
	braco2.x = tronco.x;
	braco2.y = -tronco.bot + tronco.y;
	braco2.z = tronco.z + tronco.h/1.5;
	
	//chapeu
	chapeu.bot = cabeca.bot;
	chapeu.top = 0;
	chapeu.h = cabeca.bot/1.2;
	chapeu.x = tronco.x;
	chapeu.y = tronco.y;
	chapeu.z = cabeca.z + cabeca.h; 
	
	//luva1
	luva1.x = braco1.x;
	luva1.y = braco1.y+braco1.h;
	luva1.z = braco1.z; 
	
	//luva2
	luva2.x = braco2.x;
	luva2.y = braco2.y-braco2.h;
	luva2.z = braco2.z;
	
	//pe1 (dir)
	pe1.x = pernaDir.x + ( sin( pernaDir.r1 * (pi/180) ) * (pernaDir.h));;
	pe1.y = pernaDir.y;
	pe1.z = pernaDir.z + ( cos( pernaDir.r1 * (pi/180) ) * (-pernaDir.h));
	
	//pe2
	pe2.x = pernaEsq.x + ( sin( pernaEsq.r1 * (pi/180) ) * (pernaEsq.h));
	pe2.y = pernaEsq.y;
	pe2.z = pernaEsq.z + ( cos( pernaEsq.r1 * (pi/180) ) * (-pernaEsq.h));
	
	//Olho1
	olho1.x = cabeca.x; 
	olho1.y = cabeca.y + 0.15;
	olho1.z = cabeca.z + 0.36;

	
	//Olho2
	olho2.x = cabeca.x;
	olho2.y = cabeca.y-0.15;
	olho2.z = cabeca.z + 0.36;
	
	//tampaolho1
	tampaolho1.x = cabeca.x + 0.42;
	tampaolho1.y = cabeca.y + 0.15;
	tampaolho1.z = cabeca.z + 0.36;
	
	//tampaolho2
	tampaolho2.x = cabeca.x + 0.42;
	tampaolho2.y = cabeca.y -0.15;
	tampaolho2.z = cabeca.z + 0.36;
	
	
}

void pula(){
	t+=0.01;
	if(pulo == 1){
		v += (-g) * t;
		tronco.z = tronco.z + v;
	}
	if(tronco.z <= 1.2){
		tronco.z=1.2;
		pulo = 0;
		v = v0;
		t=0;
	}
}

void frente(){
	tronco.x += vel_andar;
	if((pernaDir.r1 <= angulo_andar) && (andaDir == -1) ){
		pernaDir.r1 -= (vel_andar*100);
		if(pernaDir.r1 <= -angulo_andar){
			andaDir = 1;
		}
	}
	
	if((pernaDir.r1 >= -angulo_andar) && (andaDir == 1) ){
		pernaDir.r1 += (vel_andar*100);
		if(pernaDir.r1 >= angulo_andar)
			andaDir = -1;
	}
	
	if((pernaEsq.r1 <= angulo_andar) && (andaEsq == -1) ){
		pernaEsq.r1 -= vel_andar*100;
		if(pernaEsq.r1 <= -angulo_andar){
			andaEsq = 1;
		}
	}
	
	if((pernaEsq.r1 >= -angulo_andar) && (andaEsq == 1) ){
		pernaEsq.r1 += vel_andar*100;
		if(pernaEsq.r1 >= angulo_andar)
			andaEsq = -1;
	}
}

void tras(){
	tronco.x -= vel_andar;
		if((pernaDir.r1 <= angulo_andar) && (andaDir == -1) ){
		pernaDir.r1 -= vel_andar*100;
		if(pernaDir.r1 <= -angulo_andar){
			andaDir = 1;
		}
	}
	
	if((pernaDir.r1 >= -angulo_andar) && (andaDir == 1) ){
		pernaDir.r1 += vel_andar*100;
		if(pernaDir.r1 >= angulo_andar)
			andaDir = -1;
	}
	
	if((pernaEsq.r1 <= 30) && (andaEsq == -1) ){
		pernaEsq.r1 -= vel_andar*100;
		if(pernaEsq.r1 <= -angulo_andar){
			andaEsq = 1;
		}
	}
	
	if((pernaEsq.r1 >= -angulo_andar) && (andaEsq == 1) ){
		pernaEsq.r1 += vel_andar*100;	
		if(pernaEsq.r1 >= angulo_andar)
			andaEsq = -1;
	}
}

void direita(){
	tronco.y += 0.05;
}

void esquerda(){
	tronco.y -= 0.05;
}

void rotaciona(float n){
	angle += n;
}

static void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   gluLookAt(0.0, 6.5, 4.0,
             0.0, 0.0, 1.0,
             0.0, 0.0, 1.0);

   //angle += rot;

   glRotated(angle, 0, 0, 1);
   glColor3f(0.6, 0.6, 0.4);
   
   pula();
   
   attRobo();
   
   //Perna esq
   glPushMatrix();
      glTranslatef(pernaEsq.x, pernaEsq.y, pernaEsq.z);
      glRotatef(180,1,0,0);
      glRotatef(pernaEsq.r1,pernaEsq.r2,pernaEsq.r3,pernaEsq.r4);
      gluCylinder(qobj, pernaEsq.bot, pernaEsq.top, pernaEsq.h, 15, 1);
   glPopMatrix();
   
   //Perna dir
   glPushMatrix();
      glTranslatef(pernaDir.x, pernaDir.y, pernaDir.z);
      glRotatef(180,1,0,0);
      glRotatef(pernaDir.r1,pernaDir.r2,pernaDir.r3,pernaDir.r4);
      gluCylinder(qobj, pernaDir.bot, pernaDir.top, pernaDir.h, 15, 1);
   glPopMatrix();
   
   //tronco
   glPushMatrix();
      glTranslatef(tronco.x, tronco.y, tronco.z);
      gluCylinder(qobj, tronco.bot, tronco.top, tronco.h, 15, 1);
   glPopMatrix();
   
   //tampatronco
   glPushMatrix();
      glTranslatef(tampatronco.x, tampatronco.y, tampatronco.z);
      gluCylinder(qobj, tampatronco.top, tampatronco.bot, tampatronco.h, 15, 1);
   glPopMatrix();
   
   //pescoco
   glPushMatrix();
      glTranslatef(pescoco.x, pescoco.y, pescoco.z);
      gluCylinder(qobj, pescoco.top, pescoco.bot, pescoco.h, 15, 1);
   glPopMatrix();
   
   //cabeca
   glPushMatrix();
      glTranslatef(cabeca.x, cabeca.y, cabeca.z);
      gluCylinder(qobj, cabeca.bot, cabeca.top, cabeca.h, 15, 1);
   glPopMatrix();
   
   //braço1
   glPushMatrix();
      glTranslatef(braco1.x, braco1.y, braco1.z);
      glRotatef(braco1.r1,braco1.r2,braco1.r3,braco1.r4);
      gluCylinder(qobj, braco1.bot, braco1.top, braco1.h, 15, 1);
   glPopMatrix();
   
   //braço2
   glPushMatrix();
      glTranslatef(braco2.x, braco2.y, braco2.z);
      glRotatef(90,1,0,0);
      glRotatef(braco2.r1,braco2.r2,braco2.r3,braco2.r4);
      gluCylinder(qobj, braco2.bot, braco2.top, braco2.h, 15, 1);
   glPopMatrix();
   
   //Esfera braco1
   glPushMatrix();
      glTranslatef(braco1.x, braco1.y, braco1.z);
      glutSolidSphere(braco1.bot, 20, 20);
   glPopMatrix();
   
   //Esfera braco2
   glPushMatrix();
      glTranslatef(braco2.x, braco2.y, braco2.z);
      glutSolidSphere(braco2.bot, 20, 20);
   glPopMatrix();
   
   //Esfera perna1
   glPushMatrix();
      glTranslatef(pernaDir.x, pernaDir.y, pernaDir.z);
      glutSolidSphere(pernaDir.bot, 20, 20);
   glPopMatrix();
   
   //Esfera perna2
   glPushMatrix();
      glTranslatef(pernaEsq.x, pernaEsq.y, pernaEsq.z);
      glutSolidSphere(pernaEsq.bot, 20, 20);
   glPopMatrix();
   
   glColor3f(1.0, 0.0, 0.0);
   
   //luva1
   glPushMatrix();
      glTranslatef(luva1.x, luva1.y, luva1.z);
      glutSolidSphere(0.23, 20, 20);
   glPopMatrix();
   
   //luva2
   glPushMatrix();
      glTranslatef(luva2.x, luva2.y, luva2.z);
      glutSolidSphere(0.23, 20, 20);
   glPopMatrix();
   
   //pe1
   glPushMatrix();
      glTranslatef(pe1.x, pe1.y, pe1.z);
      glutSolidSphere(0.25, 20, 20);
   glPopMatrix();
   
   //pe2
   glPushMatrix();
      glTranslatef(pe2.x, pe2.y, pe2.z);
      glutSolidSphere(0.25, 20, 20);
   glPopMatrix();
   
   //chapeu
   glPushMatrix();
      glTranslatef(chapeu.x, chapeu.y, chapeu.z);
      gluCylinder(qobj, chapeu.bot, chapeu.top, chapeu.h, 15, 1);
   glPopMatrix();
   
   //olho1
   glPushMatrix();
      glTranslatef(olho1.x, olho1.y, olho1.z);
      glRotatef(90,0,1,0);
      gluCylinder(qobj, 0.08, 0.08, 0.42, 15, 1);
   glPopMatrix();
   
   //olho2
   glPushMatrix();
      glTranslatef(olho2.x, olho2.y, olho2.z);
      glRotatef(90,0,1,0);
      gluCylinder(qobj, 0.08, 0.08, 0.42, 15, 1);
   glPopMatrix();
   
   glColor3f(1.0, 1.0, 1.0);
   
   //tampaolho1
   glPushMatrix();
      glTranslatef(tampaolho1.x, tampaolho1.y, tampaolho1.z);
      glRotatef(90,0,1,0);
      gluCylinder(qobj, 0.08, 0, 0, 15, 1);
   glPopMatrix();
   
   //tampaolho2
   glPushMatrix();
      glTranslatef(tampaolho2.x, tampaolho2.y, tampaolho2.z);
      glRotatef(90,0,1,0);
      gluCylinder(qobj, 0.08, 0, 0, 15, 1);
   glPopMatrix();
   
   glColor3f(0.0, 0.0, 0.0);
   
   //centroolho1
   glPushMatrix();
      glTranslatef(tampaolho1.x+0.01, tampaolho1.y, tampaolho1.z);
      glRotatef(90,0,1,0);
      gluCylinder(qobj, 0.02, 0, 0, 15, 1);
   glPopMatrix();
   
   //centroolho2
   glPushMatrix();
      glTranslatef(tampaolho2.x+0.01, tampaolho2.y, tampaolho2.z);
      glRotatef(90,0,1,0);
      gluCylinder(qobj, 0.02, 0, 0, 15, 1);
   glPopMatrix();
   
   glColor3f(0.5, 0.5, 0.5);
   
   //chão
   glPushMatrix();
      glTranslatef(0,0,-0.25);
      gluCylinder(qobj, 10, 0, 0, 4, 1);
   glPopMatrix();
   
	

   glFlush();
   glutSwapBuffers();
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
    switch (key) {
            case ESCAPE: 
                exit(0);
                break;
            case ' ':
				pulo=1;
				break;
			case FRENTE:
				frente();
				break;
			case TRAS:
				tras();
				break;
			case DIR:
				direita();
				break;
			case ESQ:
				esquerda();
				break;
			case 'u':
				rotaciona(-1.5);
				break;
			case 'i':
				rot = 0;
				break;
			case 'o':
				rotaciona(1.5);
				break;

    }
    glutPostRedisplay();
}


int main (int argc, char **argv)
{
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	
	
	initRobo();
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(800,600);
    glutCreateWindow("Robô");

     glutDisplayFunc(display);
    glutIdleFunc( display );
    glutKeyboardFunc(GerenciaTeclado);

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

    GLfloat light_ambient[] =  {  0.0,  0.0,  0.0, 1.0 };
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
