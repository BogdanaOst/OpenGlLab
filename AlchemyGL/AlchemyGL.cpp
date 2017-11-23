#include "stdafx.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h> 
#include <fstream>
#include <GL/freeglut.h>
#include <cstdio>
#include <string>
#include <stdarg.h>
#include <math.h>
#include <Windows.h>
#define GL_GLEXT_PROTOTYPES


#define M_PI 3.14

PFNGLMULTITEXCOORD2FARBPROC     glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB = NULL;
GLUquadricObj  *qsphere;
GLUquadricObj  *qcyl;
float lamp = 0.8;
float lamp1 = 0.8;
float lamp2 = 0.7;
int vkl123 = 11;
int vkl45 = 11;
GLfloat xRotated, yRotated, zRotated, x1Rotated, y1Rotated, z1Rotated, x2Rotated, y2Rotated, z2Rotated;
// Torus
GLdouble innerRaidus = 0.01;
GLdouble outterRaidus = 0.04;
GLint sides = 30;
GLint rings = 30;
// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void krishka();
void idleTorus();
//void idleSfera();
void specialKeys(unsigned char key, int x, int y);
void initCandleLight(double x, double y, double z, double heigh, double thick, double stand, int i);
void Init();
void room();
void port();
void cylin();
void bookshelf(double x, double y, double z);
void door();
void plate(double x, double y, double z);
void candle(double x, double y, double z, double heigh, double thick, double stand, int i);
void candlestand(double thick, double stand);
void ladder(float w, float h, float r);
void tor();
void magic(double x, double y, double z, GLdouble secs);
void book(double x, double y, double z, double thick, double ang);
void updoor();
void scroll();
GLdouble get_secs();
int move = 0;

void chair();
void fireplace(GLdouble secs);
void kolba(double x, double y, double z, int liqui);
void kolba1(double x, double y, double z, int liqui);
void table(double topWid1, double topWid2, double topThick, double legThick, double legLen);
GLuint LoadTexture(const char * filename, int width, int height);
void glWrite(float x, float y, int *font, char text[256], int kls);
void make_viewpoint();

int light = 0;
// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
const int N = 49;//new
double m = 2; //длина стен

double eye_y = 0.1;
double eye_x = 0;
double eye_z = 0.8;

double look_x = 0;
double look_z = -3;//
double look_y = 0;

double Angle = 3 * M_PI / 2;
double angle = 0;

GLuint texture[30];
char ** predictions;
int len[10];
int write = -1;
void Move() {
	
	switch (move)
	{
	   case 0:
	   
		look_x = 0;
		look_z = -0.7;
		look_y = 0;

		eye_y = 0.1;
		eye_x = 0;
		eye_z = 0.8;
		Angle = 3 * M_PI / 2;
		move = 1;
	   break;

	   case 1:
		   Angle -= M_PI / 72;
		   eye_x += 0.04 * cos(3 * M_PI / 2 - Angle);
		   eye_z -= 0.06 * sin(3 * M_PI / 2 - Angle);
		   if (Angle < M_PI)
		   {
			   move = 2;
			   look_z = 0.9;
			   Angle = 2 * M_PI / 3;
		   }
	   break;

	   case 2:
		   eye_x -= 0.9 / 72;
		   eye_z += 1.4/72;
		   if (eye_z > 0.7)
		   {
			   move = 3;
			   look_z = -0.7;
			   Angle = 3 * M_PI / 2;
		   }

	   break;

	   case 3:

		   Angle += M_PI / 72;
		   eye_x += 0.04 * sin(/*3 * M_PI / 2 - */Angle);
		   eye_z -= 0.06 * cos(/*3 * M_PI / 2 - */Angle);
		   if (Angle > 4*M_PI/2)
		   {
			   move = 0;
			   Angle -= 2 * M_PI;
		   }

	   break;
	
	}

}

/*GLuint texture[1];*/
// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]) {

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);
	/*glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");*/
	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window

	glutInitWindowSize(600, 600);
	//glutReshapeFunc(reshape(600, 600));
	glutCreateWindow("Alchemistry");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	/*make_viewpoint();*/

	Init();
	initCandleLight(-0.55, -.15, -0.4, 0.1, 0.03, 0.1, 1);
	initCandleLight(-0.58, -.15, -0.45, 0.07, 0.015, 0, 2);
	initCandleLight(0.56, -.15, -0.32, 0.07, 0.013, 0.05, 3);
	initCandleLight(-0.61, -.15, -0.34, 0.03, 0.035, 0, 4);
	initCandleLight(0.63, -.15, -0.3, 0.07, 0.011, 0.07, 5);
	//Init1();
	//Init2();

	// Callback functions	
	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutKeyboardFunc(specialKeys);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	xRotated = yRotated = zRotated = 30.0;
	xRotated = 33;
	yRotated = 40;
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//Assign  the function used in events
	glutDisplayFunc(display);
	texture[0] = LoadTexture("images/parket.bmp", 256, 512);
	texture[1] = LoadTexture("images/yellow brick.bmp", 512, 256);
	texture[2] = LoadTexture("images/sk1.jpg", 544, 321);
	texture[10] = LoadTexture("images/water.bmp", 256, 256);
	texture[4] = LoadTexture("images/wall.bmp", 256, 128);
	texture[5] = LoadTexture("images/dr1.bmp", 133, 250);
	texture[6] = LoadTexture("images/wood1.bmp", 200, 200);
	texture[7] = LoadTexture("images/book5.bmp", 128, 256);
	texture[8] = LoadTexture("images/book2.bmp", 1024, 512);
	texture[9] = LoadTexture("images/book3.bmp", 1024, 512);
	texture[3] = LoadTexture("images/book4.bmp", 1024, 512);
	texture[11] = LoadTexture("images/fire_.bmp", 256, 256);
	texture[12] = LoadTexture("images/gold.bmp", 512, 256);
	texture[13] = LoadTexture("images/magic1.bmp", 512, 256);
	texture[14] = LoadTexture("images/port.bmp", 256, 400);
	texture[15] = LoadTexture("images/wax1.bmp", 256, 256);
	texture[16] = LoadTexture("images/obs.bmp", 256, 256);
	texture[17] = LoadTexture("images/fireplace.bmp", 400, 256);
	texture[18] = LoadTexture("images/fire1.bmp", 400, 256);
	texture[19] = LoadTexture("images/fire2.bmp", 400, 256);
	texture[20] = LoadTexture("images/fire3.bmp", 400, 256);
	texture[21] = LoadTexture("images/fire4.bmp", 400, 256);
	texture[22] = LoadTexture("images/fire5.bmp", 400, 256);
	texture[23] = LoadTexture("images/brick025.bmp", 400, 256);
	texture[24] = LoadTexture("images/shelf.bmp", 400, 256);

	predictions = new char *[10];
	predictions[0] = new char[255];
	predictions[0] = (char*)"Give us 27 out of 27 pleeease";
	len[0] = 29;
	predictions[1] = new char[255];
	predictions[1] = (char*)"We will be happier with less amount of labs";
	len[1] = 29;


	//glutReshapeFunc(reshapeTorus);
	glutIdleFunc(idleTorus);
	//	glutIdleFunc(idleSfera);
	//glutIdleFunc(get_secs);
	qsphere = gluNewQuadric();
	//  Pass control to GLUT for events


	glutMainLoop();

	//  Return to OS
	return 0;

}


void make_viewpoint() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.01, 5);
	gluLookAt(eye_x, eye_y, eye_z,

		look_x, look_y, look_z,

		0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display() {
	
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//
	glEnable(GL_LIGHTING);

	// двухсторонний расчет освещения 
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// автоматическое приведение нормалей к
	// единичной длине
	glEnable(GL_NORMALIZE);
	////
	make_viewpoint();
	// Reset transformations
	glLoadIdentity();


	door();
	updoor();
	book(-0.6, -0.12, -0.9, 0.01, 20);
	book(-0.45, -0.17, -0.9, 0.03, 90);
	book(-0.42, -0.14, -0.9, 0.02, 90);
	book(-0.19, -0.12, -0.9, 0.015, -10);
	port();
	ladder(0.15, .95, 0.01);
	//kartina();

	room();


	
	table(1.5, 0.5, 0.05, 0.05, 0.3);
	bookshelf(-0.4, 0.1, -1);
	bookshelf(0.4, 0.1, -1);
	plate(0.45, -0.15, -0.45);

	candle(-0.55, -.15, -0.4, 0.1, 0.03, 0.1,1);
	candle(-0.58, -.15, -0.45, 0.07, 0.015, 0,2);
	candle(0.56, -.15, -0.32, 0.07, 0.013, 0.05, 3);
	candle(-0.61, -.15, -0.34, 0.03, 0.035, 0,4);
	candle(0.63, -.15, -0.3, 0.07, 0.011, 0.07,5);


	

	//room();

	kolba(-0.3, -0.16, -0.6, 0);
	kolba(0.3, -0.16, -0.6, 10);
	kolba1(-0.45, -0.12, -0.5, 11);

	GLfloat secs = get_secs();
	magic(0, -0.05, -0.5, secs);
	fireplace(secs);
	//glWrite(-0.1, 0.1, (int*)GLUT_BITMAP_9_BY_15, (char*)"typaya laba", 11);
	//if (write >= 0) scroll();//glWrite(-0.1, 0.1, (int*)GLUT_BITMAP_9_BY_15, predictions[write], len[write]);

	//cylin();

	glFlush();
	glutSwapBuffers();

}
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------

void specialKeys(unsigned char key, int x, int y) {
	if (GetAsyncKeyState(0x57)) key = 'w';
	if (GetAsyncKeyState(0x41)) key = 'a';
	if (GetAsyncKeyState(0x53)) key = 's';
	if (GetAsyncKeyState(0x44)) key = 'd';
	if (GetAsyncKeyState(0x55)) key = 'u';
	if (GetAsyncKeyState(0x48)) key = 'h';
	if (GetAsyncKeyState(0x4A)) key = 'j';
	if (GetAsyncKeyState(0x4B)) key = 'k';
	if (GetAsyncKeyState(0x4D)) key = 'm';
	if (GetAsyncKeyState(0x20)) key = '_';

	switch (key) {
	case 'w':
		write = -1;
		move = 0;
		if (Angle >= 0 && Angle <= M_PI) {
			if (eye_z < m / 2 - 0.1) {
				eye_z += 0.02 * sin(Angle);
				if (Angle >= 0 && Angle <= M_PI / 2) {
					if (eye_x < 0.75)eye_x += 0.02 * cos(Angle);
				}
				else {
					if (eye_x > -0.75)eye_x += 0.02 * cos(Angle);
				}
			}
		}
		else {
			if (eye_z > -m / 2 + 0.1) {
				eye_z += 0.02 * sin(Angle);
				if (Angle >= 3 * M_PI / 2) {
					if (eye_x < 0.75) eye_x += 0.02 * cos(Angle);
				}
				else {
					if (eye_x > -0.75)eye_x += 0.02 * cos(Angle);
				}
			}
		}
		break;
	
	case 's':
		write = -1;
		move = 0;
		if (Angle >= 0 && Angle <= M_PI) {
			if (eye_z > -m / 2 + 0.1) {
				eye_z -= 0.02 * sin(Angle);
				if (Angle >= 0 && Angle <= M_PI / 2) {
					if (eye_x > -0.75)eye_x -= 0.02 * cos(Angle);
				}
				else {
					if (eye_x < 0.75)eye_x -= 0.02 * cos(Angle);
				}
			}
		}
		else {
			if (eye_z < m / 2 - 0.1) {
				eye_z -= 0.02 * sin(Angle);
				if (Angle >= 3 * M_PI / 2) {
					if (eye_x > -0.75)eye_x -= 0.02 * cos(Angle);
				}
				else {
					if (eye_x < 0.75)eye_x -= 0.02 * cos(Angle);
				}
			}
		}
		break;
	case 'a':
		write = -1;
		move = 0;
		if (Angle >= 0 && Angle <= M_PI) {
			if (eye_x < 0.9) {
				eye_x -= 0.02 * cos(Angle + M_PI / 2);
				look_x += 0.02;
				if (Angle >= 0 && Angle <= M_PI / 2) {
					if (eye_z > -m / 2 + 0.2)eye_z -= 0.02 * sin(Angle + M_PI / 2);
				}
				else {
					if (eye_z < m / 2 - 0.2)eye_z -= 0.02 * sin(Angle + M_PI / 2);
				}
			}
		}
		else {
			if (eye_x > -0.9) {
				eye_x -= 0.02 * cos(Angle + M_PI / 2);
				look_x -= 0.02;
				if (Angle >= 3 * M_PI / 2) {
					if (eye_z > -m / 2 + 0.2) eye_z -= 0.02 * sin(Angle + M_PI / 2);
				}
				else {
					if (eye_z < m / 2 - 0.2)eye_z -= 0.02 * sin(Angle + M_PI / 2);
				}
			}
		}
		break;
	case 'd':
		write = -1;
		move = 0;
		if (Angle >= 0 && Angle <= M_PI) {
			if (eye_x > -0.9) {
				eye_x += 0.02 * cos(Angle + M_PI / 2);
				look_x -= 0.02;
				if (Angle >= 0 && Angle <= M_PI / 2) {
					if (eye_z < m / 2 - 0.1)eye_z += 0.02 * sin(Angle + M_PI / 2);
				}
				else {
					if (eye_z > -m / 2 + 0.1)eye_z += 0.02 * sin(Angle + M_PI / 2);
				}
			}
		}
		else {
			if (eye_x < 0.9) {
				eye_x += 0.02 * cos(Angle + M_PI / 2);
				look_x += 0.02;
				if (Angle >= 3 * M_PI / 2) {
					if (eye_z < m / 2 - 0.1) eye_z += 0.02 * sin(Angle + M_PI / 2);
				}
				else {
					if (eye_z > -m / 2 + 0.1)eye_z += 0.02 * sin(Angle + M_PI / 2);
				}
			}
		}
		break;

	case 'u':
		move = 0;
		if (angle < M_PI / 9) {
			angle += M_PI / 72;
			look_y = 2 * sin(angle);
		}
		break;
	case 'j':
		move = 0;
		if (angle > -M_PI / 9) {
			angle += -M_PI / 72;
			look_y = 2 * sin(angle);
		}
		break;
	case 'h':
		move = 0;
		Angle -= M_PI / 36;
		if (Angle < 0) {
			Angle = 2 * M_PI + Angle;
		}
		look_x = 3 * cos(Angle);
		look_z = 3 * sin(Angle);

		break;
	case 'm':
	{
		
			Move();


		break;}
	case 'k':
		Angle += M_PI / 36;
		if (Angle > M_PI * 2) {
			Angle = Angle - M_PI * 2;
		}
		look_x = 3 * cos(Angle);
		look_z = 3 * sin(Angle);

		break;
	case '9':
			glEnable(GL_LIGHT0);
		break;
	case '0':
		glDisable(GL_LIGHT0);
		break;

	case '1':
	{
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		vkl123 = 11;
	}
		break;
	case '2':
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		vkl123 = 15;
		break;
	case '3':
		glEnable(GL_LIGHT4);
		glEnable(GL_LIGHT5);
		vkl45 = 11;
		break;
	case '4':
		glDisable(GL_LIGHT4);
		glDisable(GL_LIGHT5);
		vkl45 = 15;
		break;

	case '_':
		if (write = 0) write = -1;
		if (/*eye_x < 0.2 && eye_x > -0.2 &&*/ eye_z > -3.5 && eye_z < 0.9) {
			//зарандомить райт
			write = 0;
		}
		break;
	}


	glutPostRedisplay();
}
//
//Init light
//
void Init() {
	glShadeModel(GL_SMOOTH);

	GLfloat light_diffuse[] = { 255, 159, 57 };
	GLfloat light_ambient[] = { 255, 159, 57 };
	GLfloat light_position[] = { 0.0, -0.65, 0.94f, 0.97 };
	GLfloat light_spot_direction[] = { 0.0, 0.0, 1.0 };
	GLfloat light_specular[] = { 0.5,0.5,0.5,0.5 };
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 40);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 120);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.7);

}

GLdouble get_secs(void)
{
	return glutGet(GLUT_ELAPSED_TIME) / 1000.0;
}
void tor() {

	GLfloat s_emissive[4] = { 0, 0, 0, 0.7f };
	GLfloat s_diffuse[4] = { 0.5f, 0.5f, 0.5f, 0.7f };
	GLfloat s_specular[4] = { 0.5f, 0.5f, 0.5f, 0.7f }; //окраска 
	GLfloat s_ambient[4] = { 0.5f, 0.5f, 0.5f, 0.7f };
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glBlendFunc(GL_ONE, GL_ONE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glTranslatef(0.9, -0.2, -1.8);
	// rotation about X axis
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);
	// built-in (glut library) function , draw you a Torus.

	glutSolidTorus(innerRaidus, outterRaidus, sides, rings);
	glPopMatrix();


	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glBlendFunc(GL_ONE, GL_ONE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glTranslatef(0.9, -0.2, -1.8);
	// rotation about X axis
	glRotatef(x1Rotated, 1.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(y1Rotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(z1Rotated, 0.0, 0.0, 1.0);
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);
	// built-in (glut library) function , draw you a Torus.

	glutSolidTorus(innerRaidus, outterRaidus, sides, rings);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glBlendFunc(GL_ONE, GL_ONE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glTranslatef(0.9, -0.2, -1.8);
	// rotation about X axis
	glRotatef(x2Rotated, 1.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(y2Rotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(z2Rotated, 0.0, 0.0, 1.0);
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);
	// built-in (glut library) function , draw you a Torus.

	glutSolidTorus(innerRaidus, outterRaidus, sides, rings);
	glPopMatrix();
}
void idleTorus(void)
{

	yRotated += 0.5;
	x1Rotated += 0.5;
	z2Rotated += 0.5;
	display();
}

void port() {
	glPushMatrix();
	int y = .4;
	int z = -.5;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[14]);
	glNormal3d(1, 0, 0);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);	glVertex3d(0.99, y - .25, z + 0);
	glTexCoord2d(1, 0);
	glVertex3d(0.99, y - .25, z + .3);
	glTexCoord2d(1, 1);
	glVertex3d(0.99, y + .25, z + .3);
	glTexCoord2d(0, 1);
	glVertex3d(0.99, y + .25, z + 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[6]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glPushMatrix();
	glTranslated(0.99, y - .25, z + .155);
	glScaled(0.01, 0.02, 0.31);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.99, y, z + .3);
	glScaled(0.01, 0.5, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.99, y + .25, z + .155);
	glScaled(0.01, 0.02, 0.31);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.99, y, z + 0.01);
	glScaled(0.01, 0.5, 0.02);
	glutSolidCube(1.0);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void krishka() {
	GLfloat s_emissive[4] = { 0, 0, 0, 0.7f };
	GLfloat s_diffuse[4] = { 0.7f, 0.5f, 0.5f, 0.7f };
	GLfloat s_specular[4] = { 0.5f,0.5f, 0.5f, 0.7f }; //окраска 
	GLfloat s_ambient[4] = { 0.7f, -0.5f, 0.5f, -0.3f };

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);


	glTranslated(0.9, -0.1, -1.8);
	glRotated(-90, 1, 0, 0);

	glutSolidCylinder(0.06, 0.01, 30, 1.5);


	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);


	glTranslated(0.6, -0.1, -1.8);
	glRotated(-90, 1, 0, 0);

	glutSolidCylinder(0.06, 0.01, 30, 1.5);


	glPopMatrix();



}
void cylin() {
	GLfloat s_emissive[4] = { 0, 0, 0, 0.7f };
	GLfloat s_diffuse[4] = { 0.7f, 0.5f, 0.5f, 0.7f };
	GLfloat s_specular[4] = { 0.7f,-0.5f, 0.5f, -0.7f }; //окраска 
	GLfloat s_ambient[4] = { 0.7f, 0.5f, 0.5f, 0.3f };

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);

	glTranslated(0.9, -0.3, -1.8);
	glRotated(-90, 1, 0, 0);

	glutSolidCylinder(0.06, 0.2, 30, 1.5);

	glDisable(GL_BLEND);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);

	glTranslated(0.6, -0.3, -1.8);
	glRotated(-90, 1, 0, 0);

	glutSolidCylinder(0.06, 0.2, 30, 1.5);

	glDisable(GL_BLEND);
	glPopMatrix();
}
void room() {


	GLfloat s_emissive[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat s_diffuse[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat s_specular[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat s_ambient[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
	//glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	//glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
	//glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);


	glNormal3d(1, 0, 0);
	for (int j = 0; j<N; j++) {
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= N; i++) {
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * j);
			glVertex3d(-1, 1 * (j / (double)N - 0.5), m * (i / (double)N - 0.5));
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 *(j + 1));
			glVertex3d(-1, 1 * ((j + 1) / (double)N - 0.5), m * (i / (double)N - 0.5));
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glNormal3d(-1, 0, 0);

	for (int j = 0; j<N; j++) {
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= N; i++) {
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * (j + 1));
			glVertex3d(1, 1 * ((j + 1) / (double)N - 0.5), m * (i / (double)N - 0.5));
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 *j);
			glVertex3d(1, 1 * (j / (double)N - 0.5), m * (i / (double)N - 0.5));

		}
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glNormal3d(0, 1, 0);

	for (int j = 0; j<N; j++) {
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= N; i++) {
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * j);
			glVertex3d(2 * (i / (double)N - 0.5), -0.5, m * (j / (double)N - 0.5));
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * (j + 1));
			glVertex3d(2 * (i / (double)N - 0.5), -0.5, m * ((j + 1) / (double)N - 0.5));
		}
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glNormal3d(0, -1, 0);

	for (int j = 0; j<N; j++) {
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= N; i++) {
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * (j + 1));
			glVertex3d(2 * (i / (double)N - 0.5), 0.5, m * ((j + 1) / (double)N - 0.5));
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * j);
			glVertex3d(2 * (i / (double)N - 0.5), 0.5, m * (j / (double)N - 0.5));
		}
		glEnd();
	}
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	glNormal3d(0, 0, 1);

	for (int j = 0; j<N; j++) {
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= N; i++) {
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * (j + 1));
			glVertex3d(2 * (i / (double)N - 0.5), 1 * ((j + 1) / (double)N - 0.5), -m / 2);
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * j);
			glVertex3d(2 * (i / (double)N - 0.5), 1 * (j / (double)N - 0.5), -m / 2);

		}
		glEnd();
	}
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	glNormal3d(0, 0, -1);

	for (int j = 0; j<N; j++) {
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= N; i++) {
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * j);
			glVertex3d(2 * (i / (double)N - 0.5), 1 * (j / (double)N - 0.5), m / 2);
			glTexCoord2f(0 + 0.02 * i, 1 - 0.02 * (j + 1));
			glVertex3d(2 * (i / (double)N - 0.5), 1 * ((j + 1) / (double)N - 0.5), m / 2);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void door() {



	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glTranslated(0, -0.05, 2);
	glScaled(0.45, 0.9, 0.02);
	glutSolidCube(1.0);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}
void updoor() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[6]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glTranslated(-.8, .5, .8);
	glScaled(0.4, 0.015, 0.4);
	glutSolidCube(1.0);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glPushMatrix();
	glTranslated(-.79, .48, .95);
	glScaled(0.1, 0.01, 0.01);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.84, .5, .95);
	glScaled(0.01, 0.05, 0.01);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.74, .5, .95);
	glScaled(0.01, 0.05, 0.01);
	glutSolidCube(1.0);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void tableLeg(double thick, double len)  // draw one table leg
{

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
void chair() {

	double legLen = 0.15, legThick = 0.03;
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glTranslated(0.35, -0.35, -1.8);
	glScaled(0.22, 0.02, 0.25);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, -0.23, -1.79);
	glScaled(0.02, 0.24, 0.22);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	double dist = 0.08;
	glPushMatrix();
	glTranslated(dist + 0.34, -0.5, dist - 1.77);//+
	tableLeg(legThick, legLen);
	glTranslated(0.42, -0.5, -1 * dist - 1.7);
	tableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 1 * dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	tableLeg(legThick, legLen);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
void table(double topWid1, double topWid2, double topThick, double legThick, double legLen)
{


	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	double x = 0; //top
	double z = -m / 2 + 0.5; //
	glTranslated(x, -0.5 + legLen, z);
	glScaled(topWid1, topThick, topWid2);
	glutSolidCube(1.0);
	glPopMatrix();
	double dist = 0.95* topWid1 / 2.0 - legThick / 2.0;
	double dist2 = 0.95* topWid2 / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist - x, -0.5, dist2 + z);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist2);
	tableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist2);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist2);
	tableLeg(legThick, legLen);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
void plate(double x, double y, double z) {
	glPushMatrix();
	glTranslated(x, y, z);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[12]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	qcyl = gluNewQuadric();
	glColor3d(1, 1, 1);
	glRotated(-90, 1, 0, 0);
	gluDisk(qcyl, 0, .05, 20, 20);
	//glRotated(180, 1, 0, 0);
	//glTranslated(0, 0, .06);
	gluCylinder(qcyl, .05, .1, .04, 20, 20);

	glBindTexture(GL_TEXTURE_2D, texture[17]);
	glTranslated(0, 0, 0.015);
	gluCylinder(qcyl, 0.068, 0, .03, 20, 20);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void ladder(float w, float h, float r)
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[6]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	qcyl = gluNewQuadric();
	glTranslatef(-0.75, -0.5, 0.665);
	glRotatef(-70, 1, 0, 0);
	gluCylinder(qcyl, r, r, h, 30, 30);
	glTranslatef(w, 0, 0);
	gluCylinder(qcyl, r, r, h, 30, 30);
	glRotatef(-90, 0, 1, 0);
	for (float z = 0.0; z < h - w / 2; z += w / 2)
	{
		glTranslatef(w / 2, 0, 0);
		gluCylinder(qcyl, 0.67*r, 0.67*r, 1.0*w, 30, 30);
	}

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void initCandleLight(double x, double y, double z, double heigh, double thick, double stand, int i)
{
	GLfloat light_diffuse[] = { 255, 239, 171 }; 
	GLfloat light_position[] = { x, y + heigh + 0.01 + stand, z, 1 };
	glEnable(GL_LIGHT0 + i);
	glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0 + i, GL_POSITION, light_position);
	glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 10);
	glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 1000);
	glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 1500);
}
void candle(double x, double y, double z, double heigh, double thick, double stand, int i) {
	glPushMatrix();
	glTranslated(x, y, z);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[15]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	qcyl = gluNewQuadric();
	glColor3d(1, 1, 1);
	glRotated(-90, 1, 0, 0);

	glTranslated(0, 0, stand);
	//gluCylinder(qcyl, thick, thick, heigh, 20, 20);
	glutSolidCylinder(thick, heigh, 20, 20);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	int vkl = i < 4 ? vkl123 : vkl45;
	glBindTexture(GL_TEXTURE_2D, texture[vkl]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTranslated(0, 0, heigh + 0.01);
	glutWireSphere(0.003, 10, 10);

	//gluDisk(qcyl, 0, .1, 20, 20);
	//glRotated(180, 1, 0, 0);
	//glTranslated(0, 0, .06);


	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glTranslated(0, 0, -heigh - 0.01);
	if (stand > 0) {
		
		candlestand(thick, stand);
	}

	glPopMatrix();

	

}


void candlestand(double thick, double stand) {
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[16]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glTranslated(0, 0, -stand);
	gluCylinder(qcyl, 0.005, 0.005, stand, 20, 20);
	glutSolidCone(thick + 0.01, 0.005, 20, 20);
	glTranslated(0, 0, stand);
	glRotated(180, 1, 0, 0);
	glutSolidCone(thick + 0.02, 0.01, 20, 20);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void fireplace(GLdouble secs)
{
	glPushMatrix();

	GLfloat angle;
	/* one revolution every 10 seconds... */
	secs = secs - 2.*trunc(secs / 2.);
	//angle = (secs / 10.) * (183.);
	angle = abs(secs) *2.5;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[18 + (int)angle]);
	glNormal3d(0, 0, 1);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(0.3, -0.5f, 0.95f);
	glTexCoord2d(1, 0);
	glVertex3f(-0.3f, -0.5f, 0.95f);
	glTexCoord2d(1, 1);
	glVertex3f(-0.3f, -0.1f, 0.95f);
	glTexCoord2d(0, 1);
	glVertex3f(0.3f, -0.1f, 0.95f);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[22]);
	glPushMatrix();
	glTranslated(-.3, -.3, .975);
	glScaled(0.025, 0.4, 0.055);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.3, -.3, .975);
	glScaled(0.025, 0.4, 0.055);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -.1, .95);
	glScaled(0.66, 0.02, 0.15);
	glutSolidCube(1.0);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[23]);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glPushMatrix();
	glTranslated(0, 0.2, .95);
	glScaled(0.26, .6, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
}

//BOOKS
void book(double x, double y, double z, double thick, double ang) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTranslated(x, y, z);
	glRotated(ang, 0, 0, 0.7);
	glScaled(thick, 0.14, 0.1);
	glutSolidCube(1);


	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void bookshelf(double x, double y, double z) {


	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glTranslated(x, y, z); // -1 0 0.6
	glScaled(0.5, 0.6, 0.03);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y + 0.3, z);
	glScaled(0.5, 0.02, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y + 0.1, z);
	glScaled(0.5, 0.02, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y - 0.1, z);
	glScaled(0.5, 0.02, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y - 0.3, z);
	glScaled(0.5, 0.02, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + 0.24, y, z);
	glScaled(0.02, 0.6, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 0.24, y, z);
	glScaled(0.02, 0.6, 0.3);
	glutSolidCube(1.0);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//KOLBS
void liq(int liqui) {

	glPushMatrix();
	glTranslated(0, 0.003, 0);
	//glRotated(-90, 1, 0, 0);

	qcyl = gluNewQuadric();
	//glColor3f(1.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[liqui]);
	//liqui = (liqui + 1) % 3;

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//glutSolidCone(0.055, 0.12, 30, 1.5);
	gluCylinder(qcyl, 0.055, 0.037, 0.04, 30, 1.5);
	glTranslated(0, 0, 0.04);
	gluDisk(qcyl, 0, 0.037, 30, 1.5);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void kolba(double x, double y, double z, int liqui) {
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-90, 1, 0, 0);
	if (liqui) liq(liqui);
	//glTranslated(x, y, z);
	GLfloat s_emissive[4] = { 0, 0, 0, 0.7f };
	GLfloat s_diffuse[4] = { 0.5f, 0.5f, 0.5f, 0.7f };
	GLfloat s_specular[4] = { 0.5f, 0.5f, 0.5f, 0.7f }; //окраска 
	GLfloat s_ambient[4] = { 0.5f, 0.5f, 0.5f, 0.7f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	//glBlendFunc(GL_ONE, GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);


	//glRotated(-90, 1, 0, 0);

	qcyl = gluNewQuadric();
	gluCylinder(qcyl, 0.06, 0.02, 0.1, 30, 1.5);

	//glutSolidCone(0.06, 0.1, 60, 60);
	//glTranslated(0, 0.1, 0);
	glutSolidCylinder(0.02, 0.15, 30, 1.5);

	glDisable(GL_BLEND);
	glPopMatrix();
}
void stand() {
	glPushMatrix();
	glTranslated(0, 0, -0.05);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//glutSolidCone(0.055, 0.12, 30, 1.5);
	gluCylinder(qcyl, 0.035, 0.03, 0.01, 30, 1.5);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void liq1(int liqui) {
	glPushMatrix();
	glTranslated(0, 0.003, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[liqui]);
	//liqui = (liqui + 1) % 3;

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	qsphere = gluNewQuadric();
	gluSphere(qsphere, 0.047, 60, 60);
	glutSolidCylinder(0.017, 0.07, 30, 1.5);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void kolba1(double x, double y, double z, int liqui) {
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(-90, 1, 0, 0);
	liq1(liqui);
	GLfloat s_emissive[4] = { 0, 0, 0, 0.7f };
	GLfloat s_diffuse[4] = { 0.5f, 0.5f, 0.5f, 0.7f };
	GLfloat s_specular[4] = { 0.5f, 0.5f, 0.5f, 0.7f }; //окраска 
	GLfloat s_ambient[4] = { 0.5f, 0.5f, 0.5f, 0.7f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);

	stand();
	//настройка смешивания
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND); //делает прозрачность
						//рисование непрозрачных объектов комнаты до колбы - важно!!!!!!!!!!!!!!!!!!
						//настройки автоматического текстурирования

						//		рисоание объектов
						//glutSolidSphere(0.05, 60, 60);
	qsphere = gluNewQuadric();
	gluSphere(qsphere, 0.05, 60, 60);

	glutSolidCylinder(0.02, 0.1, 30, 1.5);
	//отключаем текстурирование и смешивание
	glDisable(GL_BLEND);
	glPopMatrix();
}
GLuint LoadTexture(const char * filename, int width, int height)
{

	GLuint texture;

	unsigned char * data;

	FILE * file;

	file = fopen(filename, "rb");

	if (file == NULL) return 0;

	data = (unsigned char *)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

void glWrite(float x, float y, int *font, char text[256], int kls) {
	glPushMatrix();
	int i;
	glRasterPos2f(x, y);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (i = 0; i < kls; i++) {
		//glColor3f(1.0f, 0.0f, 0.0f);
		glutBitmapCharacter(font, (int)text[i]);
	}
	glPopMatrix();
}

void stand1() {
	glPushMatrix();
	glTranslated(0, 0, -0.107);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[12]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	gluCylinder(qcyl, 0.045, 0.04, 0.015, 30, 1.5);
	glTranslated(0, 0, 0.015);
	gluDisk(qcyl, 0, 0.04, 30, 1.5);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void magic(double x, double y, double z, GLdouble secs) {
	glPushMatrix();

	GLfloat angle;
	/* one revolution every 10 seconds... */
	secs = secs - 6.*trunc(secs / 6.);
	//angle = (secs / 10.) * (183.);
	angle = abs(3 - secs) / 100;

	glTranslated(x, y, z);
	glRotated(-90, 1, 0, 0);
	GLfloat s_emissive[4] = { 0, 0, 0, 0.7f };
	GLfloat s_diffuse[4] = { 0.5f, 0.5f, 0.5f, 0.7f };
	GLfloat s_specular[4] = { 0.5f, 0.5f, 0.5f, 0.7f }; //окраска 
	GLfloat s_ambient[4] = { 0.5f, 0.5f, 0.5f, 0.7f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s_emissive);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);

	stand1();
	glTranslated(0, 0, angle);
	//настройка смешивания
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[13]);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//glRotated(90, 1, 0, 0);
	qsphere = gluNewQuadric();
	gluSphere(qsphere, 0.1, 60, 60);
	//отключаем текстурирование и смешивание
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void scroll() {
	glPushMatrix();
	int y = .4;
	int x = 0;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glNormal3d(0, 0, -1);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);	glVertex3d(-.3, .25, -0.5);
	glTexCoord2d(1, 0);
	glVertex3d(.3, .25, -0.5);
	glTexCoord2d(1, 1);
	glVertex3d(.3, .35, -0.5);
	glTexCoord2d(0, 1);
	glVertex3d(-.3, .35, -0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}