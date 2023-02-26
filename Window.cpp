#include "Window.h"
#include <iostream>

int Window::width = 800, Window::lenght = 800;
int Window::mouseX = 0, Window::mouseY = 0;
ParticleList* Window::list = nullptr;

Window::Window() {
	srand(time(NULL));
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(700, 0);
	glutInitWindowSize(width, lenght);
	glutCreateWindow("Physics Engine");
	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutIdleFunc(frame);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutMotionFunc(motionMouse);
	glutPassiveMotionFunc(nonMotionMouse);
	start();
}
void Window::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (list != nullptr) {
		list->updateParticles();
	}
	drawMouse();
	glutSwapBuffers();
}
void Window::frame() {
	static float timeRunning = 0;
	if (glutGet(GLUT_ELAPSED_TIME) - (timeRunning + 12) > 0) {
		timeRunning = glutGet(GLUT_ELAPSED_TIME);
		glutPostRedisplay();
	}
}
void Window::start() {
	glClearColor(.2, .6, .6, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, lenght, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Window::mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::cout << "inicio";
		if (list != nullptr) {
			list->newParticle(10, x, -y);
		}
		else {
			list = new ParticleList(10, x, -y);
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (list != nullptr) {
			list->newParticle(8, x, -y);
		}
		else {
			//(rand() % 15) + 6
			list = new ParticleList(8, x, -y);
		}
	}
}

void Window::motionMouse(int x, int y) {
	mouseX = x;
	mouseY = y;
}

void Window::nonMotionMouse(int x, int y) {
	mouseX = x;
	mouseY = y;
}

void Window::drawMouse() {
	glPushMatrix();
	glTranslatef(0, 800, 0);
	glTranslatef(mouseX, -mouseY, 0);
	glColor3f(0, 0, 0);
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2f(0 * 2, 0 * 2);
	glVertex2f(0 * 2, -1 * 2);
	glVertex2f(0 * 2, -2 * 2);
	glVertex2f(1 * 2, -3 * 2);
	glVertex2f(1 * 2, -4 * 2);
	glVertex2f(1 * 2, -5 * 2);
	glVertex2f(2 * 2, -6 * 2);
	glVertex2f(2 * 2, -7 * 2);
	glVertex2f(3 * 2, -8 * 2);
	glVertex2f(4 * 2, -8 * 2);
	glVertex2f(4 * 2, -9 * 2);
	glVertex2f(5 * 2, -9 * 2);
	glVertex2f(6 * 2, -9 * 2);
	glVertex2f(7 * 2, -9 * 2);
	glVertex2f(8 * 2, -8 * 2);
	glVertex2f(9 * 2, -7 * 2);
	glVertex2f(9 * 2, -6 * 2);
	glVertex2f(9 * 2, -5 * 2);
	glVertex2f(9 * 2, -4 * 2);
	glVertex2f(8 * 2, -4 * 2);
	glVertex2f(8 * 2, -3 * 2);
	glVertex2f(7 * 2, -2 * 2);
	glVertex2f(6 * 2, -2 * 2);
	glVertex2f(5 * 2, -1 * 2);
	glVertex2f(4 * 2, -1 * 2);
	glVertex2f(3 * 2, -1 * 2);
	glVertex2f(2 * 2, 0 * 2);
	glVertex2f(1 * 2, 0 * 2);
	
	glVertex2f(7 * 2, -7 * 2);
	glVertex2f(6 * 2, -6 * 2);
	glVertex2f(5 * 2, -5 * 2);
	glVertex2f(4 * 2, -4 * 2);
	glEnd();
	glColor3f(.38, .7, .13);
	glBegin(GL_POINTS);
	glVertex2f(1 * 2, -1 * 2);
	glVertex2f(2 * 2, -1 * 2);
	glEnd();
	glColor3f(.35, .67, .11);
	glBegin(GL_POINTS);
	glVertex2f(1 * 2, -2 * 2);
	glVertex2f(2 * 2, -2 * 2);
	glVertex2f(3 * 2, -2 * 2);
	glVertex2f(4 * 2, -2 * 2);
	glVertex2f(5 * 2, -2 * 2);
	glEnd();
	glColor3f(.32, .64, .09);
	glBegin(GL_POINTS);
	glVertex2f(2 * 2, -3 * 2);
	glVertex2f(3 * 2, -3 * 2);
	glVertex2f(4 * 2, -3 * 2);
	glVertex2f(5 * 2, -3 * 2);
	glVertex2f(6 * 2, -3 * 2);
	glVertex2f(7 * 2, -3 * 2);
	glEnd();
	glColor3f(.29, .61, .07);
	glBegin(GL_POINTS);
	glVertex2f(2 * 2, -4 * 2);
	glVertex2f(3 * 2, -4 * 2);
	glVertex2f(5 * 2, -4 * 2);
	glVertex2f(6 * 2, -4 * 2);
	glVertex2f(7 * 2, -4 * 2);
	glEnd();
	glColor3f(.26, .58, .05);
	glBegin(GL_POINTS);
	glVertex2f(2 * 2, -5 * 2);
	glVertex2f(3 * 2, -5 * 2);
	glVertex2f(4 * 2, -5 * 2);
	glVertex2f(6 * 2, -5 * 2);
	glVertex2f(7 * 2, -5 * 2);
	glVertex2f(8 * 2, -5 * 2);
	glEnd();
	glColor3f(.23, .55, .03);
	glBegin(GL_POINTS);
	glVertex2f(3 * 2, -6 * 2);
	glVertex2f(4 * 2, -6 * 2);
	glVertex2f(5 * 2, -6 * 2);
	glVertex2f(7 * 2, -6 * 2);
	glVertex2f(8 * 2, -6 * 2);
	glEnd();
	glColor3f(.20, .58, .1);
	glBegin(GL_POINTS);
	glVertex2f(3 * 2, -7 * 2);
	glVertex2f(4 * 2, -7 * 2);
	glVertex2f(5 * 2, -7 * 2);
	glVertex2f(6 * 2, -7 * 2);
	glVertex2f(8 * 2, -7 * 2);
	glEnd();
	glColor3f(.17, .52, .0);
	glBegin(GL_POINTS);
	glVertex2f(5 * 2, -8 * 2);
	glVertex2f(5 * 2, -8 * 2);
	glVertex2f(5 * 2, -8 * 2);
	glVertex2f(5 * 2, -8 * 2);
	glVertex2f(7 * 2, -8 * 2);
	glVertex2f(6 * 2, -8 * 2);

	glEnd();
	glPopMatrix();
}