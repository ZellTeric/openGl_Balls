#pragma once
#include <GL/GLUT.h>
#include <math.h>
#include <time.h>

namespace maths {
	const float GRAVITY = 9.81;
}

class Particle {
private:
	Particle* Next = nullptr;
	float posX, posY;
	int ratio, ID;
	float mass, time = 0, colorR, colorG, colorB;
	bool onCollision = false, microCollisionY = false, microCollisionX = false;
	//vectores
	float velocityX, velocityY;
	float acelerationX, acelerationY;
public:
	Particle(int R, int x, int y, int id);
	void draw();
	void fall();
	void update();
	bool floorColission();
	bool wallColission();
	bool cielCollition();
	friend class ParticleList;
};

class ParticleList {
private:
	Particle* Start;
	Particle* End;
	Particle* Move;
	Particle* Compare;
	float time = 0;
public:
	ParticleList(int Ratio, int x, int y);
	void updateParticles();
	void newParticle(int Ratio, int x, int y);
	void getTime();
	void collisionDetector();
};