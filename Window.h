#pragma once
#include <GL/GLUT.h>
#include "Features.h"
#include <time.h>

class Window {
private:
	static int width, lenght;
	static int mouseX, mouseY;
public:
	Window();
	static void draw();
	static void frame();
	static void mouse(int button, int state, int x, int y);
	static void drawMouse();
	static void start();
	static void motionMouse(int x, int y);
	static void nonMotionMouse(int x, int y);
	static ParticleList* list;
};