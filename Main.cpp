#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "kitcatEngine.hpp"

using namespace std;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///camera setup
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units
    ///end camera setup

	glPushMatrix();
	//glTranslatef(SCREEN_X-1,0,0);
	glScalef(3,1,0);
	glRotatef(_angle,1,1,1);
    glutWireCube(1);
    glPopMatrix();


	glutSwapBuffers();
}

void update(int value) {
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	_ang_tri += 2.0f;
	if (_ang_tri > 360) {
		_ang_tri -= 360;
	}

	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	//glutInitWindowPosition(200,100);

	//Create the window
	glutCreateWindow("Transformations");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
    glutKeyboardFunc(MyKeyboardFunc);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0); //Add a timer
    glutFullScreen();
	glutMainLoop();
	return 0;
}