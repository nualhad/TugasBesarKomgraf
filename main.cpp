#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

static GLfloat spin = 0.0;
float angle = 0;
GLuint texture[2];

float lastx, lasty;
GLint stencilBits;
static int Vx = 80;
static int Vy = 84;
static int Vz = 100;

float rot = 0;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

float _angle = 60.0f;

const GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat light_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat light_ambient2[] = { 0.3f, 0.3f, 0.3f, 0.0f };
const GLfloat light_diffuse2[] = { 0.3f, 0.3f, 0.3f, 0.0f };

const GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void patokan(int panjang) {
	int x;
	glPushMatrix();
	for (x = 0; x < panjang; x++) {
		glutSolidCube(10);
		glTranslated(10.0, 0.0, 0.0);
	}
	glPopMatrix();

	glPushMatrix();
	for (x = 0; x < panjang; x++) {
		glTranslated(-10.0, 0.0, 0.0);
		glutSolidCube(10);
	}
	glPopMatrix();
}

//bawah kandang
void bawahKandang(int lebar) {
	int zplus;
	int zmin;
	patokan(10);
	glPushMatrix();
	for (zplus = 0; zplus < lebar; ++zplus) {
		glTranslated(0.0, 0.0, 10.0);
		patokan(10);
	}
	glPopMatrix();
	glPushMatrix();
	for (zmin = 0; zmin < lebar; ++zmin) {
		glTranslated(0.0, 0.0, -10.0);
		patokan(10);
	}
	glPopMatrix();
}
// atas kandang
void AtasKandang(int lebar) {
	int zplus;
	int zmin;
	patokan(1);
	//patokan(-2);
	glPushMatrix();

	for (zplus = 0; zplus < lebar; ++zplus) {
		glTranslated(0.0, 0.0, 10.0);

		patokan(10);
	}
	glPopMatrix();
	glPushMatrix();
	for (zmin = 0; zmin < lebar; ++zmin) {
		glTranslated(0.0, 0.0, -10.0);
		patokan(10);
	}
	glPopMatrix();
}


void cube()
	{
	//menggambar kubus dan transformasi tarnslasi ke titik 0.5 0.5 0.5 dan skala 1 1 1
	glPushMatrix();
	glTranslated(0.5,0.5,0.5);//cube
	glScaled(15.0,15.0,200);
	glutSolidCube(1.0);
	glPopMatrix();
	}


void display(void) {
	glClearStencil(0); //clear the stencil buffer
	glClearDepth(1.0f);

	glClearColor(0.8, 0.7, 0.8, 0.2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //clear the buffers
	glLoadIdentity();
	gluLookAt(Vx, Vy, Vz, 0.0, 0.0, 5.0, 0.0, 1.0, 0.0);

	// kayu-1
	glPushMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(90.0, 100.0, 0.0);
	cube();
	glPopMatrix();

	// kayu-2
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(90.0, -100.0, 0.0);
	cube();
	glPopMatrix();

	// kayu-3
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(-100.0, 100.0, 0.0);
	cube();
	glPopMatrix();

	// kayu-4
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(-100.0, -100.0, 0.0);
	cube();
	glPopMatrix();

	//bawahkandang
	glPushMatrix();
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColor3f(1.0, 0.4, 0.0);
	bawahKandang(10);
	glPopMatrix();


	//ataskandang
	glPushMatrix();
	glColor3f(0.0, 0.1, 0.0);
	glTranslated(0.0, 100.0, 0.0);
	AtasKandang(10);
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
	rot++;
	angle++;
}

void init(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE);
}

static void keyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_HOME:
		Vy++;
		break;
	case GLUT_KEY_END:
		Vy--;
		break;
	case GLUT_KEY_UP:
		Vz--;
		break;
	case GLUT_KEY_DOWN:
		Vz++;
		break;

	case GLUT_KEY_RIGHT:
		Vx++;
		break;
	case GLUT_KEY_LEFT:
		Vx--;
		break;

	case GLUT_KEY_F1: {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	}
		;
		break;
	case GLUT_KEY_F2: {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient2);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse2);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	}
		;
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'd') {

		spin = spin - 1;
		if (spin > 360.0)
			spin = spin - 360.0;
	}
	if (key == 'a') {
		spin = spin + 1;
		if (spin > 360.0)
			spin = spin - 360.0;
	}
	if (key == 'q') {
		Vz+=5;
	}
	if (key == 'e') {
		Vz-=5;
	}
	if (key == 's') {
		Vy-=5;
	}
	if (key == 'w') {
		Vy+=5;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH); //add a stencil buffer to the window
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hamster Cage ala chef");
	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);

	glutKeyboardFunc(keyboard);

	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glutMainLoop();
	return 0;
}

