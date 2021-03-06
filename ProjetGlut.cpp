#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <glut.h>
#include <math.h>

using namespace std;
double ran_range(float a, float b);


#define M_PI 3.14159265

float angleZ = 0.0;
float angleY = 0.0;
float angleX = 0.0;
float scale = 0.9;

boolean mouseEnfonce = false;
float rotateFirst = 0 , orientation = -1;

float firstSpeed = 0;

GLUquadricObj *quadOBJ = gluNewQuadric();

static void gear(GLfloat inner_radius, GLfloat outer_radius, GLfloat width, GLint teeth, GLfloat tooth_depth)
{
	GLint i;
	GLfloat r0, r1, r2;
	GLfloat angle, da;
	GLfloat u, v, len;

	r0 = inner_radius;
	r1 = outer_radius - tooth_depth / 2.0;
	r2 = outer_radius + tooth_depth / 2.0;

	da = 2.0 * M_PI / teeth / 4.0;

	glShadeModel(GL_FLAT);

	glNormal3f(0.0, 0.0, 1.0);

	//draw front face 
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
		glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
		glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
		glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
	}
	glEnd();

	// draw front sides of teeth 
	glBegin(GL_QUADS);
	da = 2.0 * M_PI / teeth / 4.0;
	for (i = 0; i < teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;

		glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
		glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
		glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
		glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
	}
	glEnd();

	glNormal3f(0.0, 0.0, -1.0);

	//draw back face 
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;
		glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
		glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
		glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
		glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
	}
	glEnd();

	// draw back sides of teeth 
	glBegin(GL_QUADS);
	da = 2.0 * M_PI / teeth / 4.0;
	for (i = 0; i < teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;

		glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
		glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
		glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
		glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
	}
	glEnd();

	// draw outward faces of teeth 
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;

		glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
		glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
		u = r2 * cos(angle + da) - r1 * cos(angle);
		v = r2 * sin(angle + da) - r1 * sin(angle);
		len = sqrt(u * u + v * v);
		u /= len;
		v /= len;
		glNormal3f(v, -u, 0.0);
		glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
		glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
		glNormal3f(cos(angle), sin(angle), 0.0);
		glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
		glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
		u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
		v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
		glNormal3f(v, -u, 0.0);
		glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
		glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
		glNormal3f(cos(angle), sin(angle), 0.0);
	}

	glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
	glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

	glEnd();

	glShadeModel(GL_SMOOTH);

	//draw inside radius cylinder 
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= teeth; i++) {
		angle = i * 2.0 * M_PI / teeth;

		glNormal3f(-cos(angle), -sin(angle), 0.0);
		glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
		glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
	}
	glEnd();

}

#define nbSpheres 100 //nombre de goutes
typedef struct waterDrop {
	float x; //coordonée x
	float y; //coordonée y
	float z; //coordonée z
	float r; //rayon de la goute
	boolean reached; //goute en collision
	boolean falling; //si entrain de tomber
	float frameSpd; //vitesse de la chute
	float alpha; //opacité de la goute
};
waterDrop waterDrops[nbSpheres];

float minY = 3, maxY = 30;


double choose(double a, double b) {
	if ((double)rand() / RAND_MAX > 0.5f)
		return a;
	return b;
}

void initSphere(int i) {

	waterDrops[i].x = ran_range(2.0, 5.0);
	waterDrops[i].y = ran_range(minY, maxY);
	waterDrops[i].alpha = 0;
	waterDrops[i].z = ran_range(-2.0, 2.0);
	waterDrops[i].r = ran_range(0.1, 0.7);
	waterDrops[i].frameSpd = -ran_range(0.4, 0.8);

}

void initSpheres() {
	for (int i = 0; i < nbSpheres; i++) {
		initSphere(i);
		waterDrops[i].y = ran_range(minY, maxY);		
		waterDrops[i].reached = false;
		waterDrops[i].falling = false;
	}
}

void drawWaterDrop(int i) {

	glPushMatrix();
	glTranslatef(waterDrops[i].x, waterDrops[i].y, waterDrops[i].z);
	glColor4f(0.0, 0.5, 1.0, waterDrops[i].alpha);
	glutSolidSphere(waterDrops[i].r, 50, 50);
	glPopMatrix();

}

void animateWater() {

	for (int i = 0; i < nbSpheres; i++) {

		if (waterDrops[i].falling && waterDrops[i].reached == false) {
			waterDrops[i].y += waterDrops[i].frameSpd;
			drawWaterDrop(i);
		}

		if (waterDrops[i].y <= minY) {

			firstSpeed += 0.8;
			waterDrops[i].reached = true;
			initSphere(i);

			if (!mouseEnfonce) {
				waterDrops[i].falling = false;
			}

		}
		else {
			if (waterDrops[i].reached == true) {
				firstSpeed -= 0.79;

				waterDrops[i].reached = false;
			}
			if (waterDrops[i].alpha + 0.01 < 1)
				waterDrops[i].alpha += 0.01;
			else
				waterDrops[i].alpha = 1;

		}
	}
}


double ran_range(float a, float b) {

	return (b - a)*(double)rand() / RAND_MAX + a;

}


void projection() {

	glMatrixMode(GL_PROJECTION);
	gluPerspective(30, 1, 0.1, 500);
	gluLookAt(0, 4, 90, 0, 0, 0, 0, 1, 0);

}
float maxSpeed = 0;
void display() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(angleX, 0.0, 0.0, 1.0);
	glRotatef(angleY + 230, 0.0, 1.0, 0.0);

	glScalef(scale, scale, scale);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//for (float i = 0; i < 1; i += 0.01) {
	//	glColor4f(1.0, 1.0, 1.0, 1-i);		
	//	glutSolidSphere(i, 50, 50);
	//}

	glTranslatef(0, -10, -15);

	animateWater();

	GLfloat in_Rad_1_Gear = 1.0, out_Rad_1_Gear = 4.0, width_1_gear = 5.0;
	GLfloat height_cyl_1 = 20;
	GLfloat out_Rad_2_Gear = 3.0, width_2_gear = 0.6;
	GLfloat in_Rad_3_Gear = 0.7, out_Rad_3_Gear = 3.0, width_3_gear = 0.6;
	GLfloat height_cyl_2 = 15.0;
	GLfloat in_Rad_4_Gear = 0.3, out_Rad_4_Gear = 1.0, width_4_gear = 1.5;
	GLfloat height_cyl_3 = 2.0;
	GLfloat widthdenamo = 3.0, huightdenamo = 5.0;


	cout << firstSpeed << mouseEnfonce << "\n";

	if (mouseEnfonce) {
		maxSpeed = firstSpeed;
	}
	if (!mouseEnfonce && firstSpeed > 0) {
		firstSpeed -= maxSpeed / 300;
	}

	//initial gear (watter)
	glPushMatrix();
	glColor4f(0.65, 0.32, 0, 1.0);
	rotateFirst = (rotateFirst<-360) ? 0 : (rotateFirst - firstSpeed);
	glRotatef(rotateFirst, 0, 0, 1);
	gear(in_Rad_1_Gear, out_Rad_1_Gear, width_1_gear, 10, 5);
	glPopMatrix();

	//first cylinder (transmetteur 1)
	glPushMatrix();
	glColor4f(0.69, 0.69, 0.69, 1.0);
	gluCylinder(quadOBJ, in_Rad_1_Gear, in_Rad_1_Gear, height_cyl_1, 10.0, 10.0);
	glPopMatrix();

	
	//second gear
	glPushMatrix();
	glColor4f(0.19, 0.38, 0.38, 1.0);
	glTranslatef(0.0, 0.0, height_cyl_1);
	glRotatef(rotateFirst*1.5, 0, 0, 1);
	gear(in_Rad_1_Gear, out_Rad_2_Gear, width_2_gear, 10, 1);
	glPopMatrix();

	//third gear
	glPushMatrix();
	glTranslatef(0.0, -3, height_cyl_1 + 3);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(rotateFirst * 3, 0, 0, 1);
	gear(in_Rad_3_Gear, out_Rad_3_Gear, width_3_gear, 10, 1);
	glPopMatrix();

	//second cylinder (transmetteur 2)
	glPushMatrix();
	glColor4f(0.69, 0.69, 0.69, 1.0);
	glTranslatef(0.0, height_cyl_2 - 3, height_cyl_1 + 3);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(quadOBJ, 0.7, 0.7, height_cyl_2, 10.0, 10.0);
	glPopMatrix();

	//Last gear
	glPushMatrix();
	glColor4f(0.19, 0.38, 0.38, 1.0);
	glTranslatef(0.0, height_cyl_2 - 3, height_cyl_1 + 3);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(rotateFirst * 4, 0, 0, 1);
	gear(in_Rad_4_Gear, out_Rad_4_Gear, width_4_gear, 15, 0.5);
	glPopMatrix();

	//third cylinder (transmetteur 3)
	glPushMatrix();
	glTranslatef(0.0, height_cyl_2 - 3 + height_cyl_3, height_cyl_1 + 3);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(quadOBJ, 0.3, 0.3, height_cyl_3, 10.0, 10.0);
	glPopMatrix();

	//Denamo
	glPushMatrix();
	glTranslatef(0.0, height_cyl_2 - 3 + height_cyl_3 + huightdenamo, height_cyl_1 + 3);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluDisk(gluNewQuadric(), 0.0, widthdenamo, 50.0, 50.0);
	gluCylinder(quadOBJ, widthdenamo, widthdenamo, 5.0, 10.0, 10.0);
	glTranslatef(0.0, 0.0, huightdenamo);
	gluDisk(gluNewQuadric(), 0.0, widthdenamo, 50.0, 50.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, height_cyl_2 - 3 + height_cyl_3 + huightdenamo + 3, height_cyl_1 + 3);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(quadOBJ, 0.1, 0.1, 3.0, 10.0, 10.0);
	glTranslatef(-0.4 * 2, 0, 0);
	gluCylinder(quadOBJ, 0.1, 0.1, 3.0, 10.0, 10.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.4, 1.5, 0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(quadOBJ, 0.7, 0.7, 1.5, 10.0, 10.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 1.5, 0);

	if (firstSpeed < 0.00001) firstSpeed = 0; //on la remit à zero à cause d'une faute de precision cpp

	if (firstSpeed > 0) {
		float rLight;

		float n = 1.6;

		for (float i = 0.01; i < firstSpeed; i += 0.07) {
			rLight = exp(i*i);
			glColor4f(1.0, 1.0, 1.0, 1 - (i / n));
			glutSolidSphere(rLight, 50, 50);
		}

	}
	glColor4f(1.0, 1.0, 1.0, 0.1);
	glutSolidSphere(1.5, 50, 50);

	glPopMatrix();

	glutSwapBuffers();

	glutPostRedisplay();
}

void keyboardRotate(int touche, int x, int y) {
	switch (touche) {
	case GLUT_KEY_UP:
		angleX = angleX + 1;
		break;
	case GLUT_KEY_DOWN:
		angleX = angleX - 1;
		break;
	case GLUT_KEY_LEFT:
		angleY = angleY - 1;
		break;
	case GLUT_KEY_RIGHT:
		angleY = angleY + 1;
		break;
	}
	//glutPostRedisplay();
}


void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			for (int i = 0; i < nbSpheres; i++) {
				waterDrops[i].falling = true;
			}

			mouseEnfonce = true;
		}
		else {

			for (int i = 0; i < nbSpheres; i++) {

				if (waterDrops[i].y>minY && waterDrops[i].y<maxY) {
					waterDrops[i].falling = true;
				}
				else {
					waterDrops[i].falling = false;
				}
			}

			mouseEnfonce = false;
		}
	}

}

int main()
{

	initSpheres();

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 80);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutCreateWindow("OpenGL TP");
	glutDisplayFunc(display);

	glutSpecialFunc(keyboardRotate);
	glutMouseFunc(mouse);
	projection();
	glEnable(GL_DEPTH_TEST);

	GLfloat WHITE[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_couleur1[] = { 0.0,0.0,0.0,1.0 };
	GLfloat light_couleur2[] = { 1.0,1.0,1.0,1.0 };
	//GLfloat light_couleur3[] = {0.0,0.0,1.0,1.0};
	GLfloat light_position[] = { 0.0,0.0,5.0,0.0 };

	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_couleur1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_couleur2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_couleur2);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);

	float s[1] = { 50 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WHITE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, s);
	glutMainLoop();

	cout << "Hello world!" << endl;
	return 0;
}
