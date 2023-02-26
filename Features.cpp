#include "Features.h"
#include <iostream>


Particle::Particle(int R, int x, int y, int id) : ratio(R), posX(x), posY(y), ID(id) {
	time = 0;
	mass = ratio / 3.14159;
	colorR = .8;
	colorG = .4;
	colorB = 0;
	velocityX = 0;
	velocityY = 0;
	acelerationX = 0;
	acelerationY = 0;
}

void Particle::draw() {
	update();
	double deegres = 0, co, ca, h;
	h = 1 / (float)ratio * 2.55;
	glPushMatrix();
	glTranslatef(0, 0, 0);
	if (onCollision == true) {
		colorR = .9;
		colorG = .6;
		colorB = 0;
	}
	glColor3f(colorR, colorG, colorB);
	glLineWidth(1);
	glTranslatef(0, 800, 0);
	glTranslatef(posX, posY, 0);
	glRotatef((atan2f(velocityX, velocityY)) * 360, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < ratio * 2.55; i++) {
		co = (ratio) * sinf(deegres);
		ca = (ratio) * cosf(deegres);
		glVertex2f(ca, co);
		deegres += h;
	}
	glEnd();
	glColor3f(0, 0, 0);
	//glBegin(GL_POINTS);
	//glVertex2f(ratio, 0);
	//glEnd();
	glPopMatrix();
}

void Particle::update(){
	fall();
}

void Particle::fall() {
	if (onCollision == false) {
		velocityY -= .3;
	}
	posX += velocityX;
	posY += velocityY;
	velocityX *= .97;
	velocityY *= .97;
	if(cielCollition() or floorColission()){
		velocityY *= -1 * .5;
		if (cielCollition()) {
			posY = -ratio + rand() % 3;
		}
		if (floorColission()) {
			posY = ratio - 800 + rand() % 3;
		}
	}
	else {
		//posY--;
	}
	if (wallColission()) {
		velocityX *= -1;
		if (posX >= -ratio + 800) {
			posX = -ratio + 800 - rand() % 3;
		}
		if (posX <= ratio + 0) {
			posX = ratio - rand() % 3;
		}
	}
}

bool Particle::cielCollition() {
	if (posY >= -ratio + 0) {
		return true;
	}
	return false;
}

bool Particle::floorColission() {
	if (posY <= ratio - 800) {
		return true;
	}
	return false;
}

bool Particle::wallColission() {
	if (posX >= -ratio + 800 or posX <= ratio + 0) {
		return true;
	}
	return false;
}



//PARTICLE LIST FUNCTIONS
//*********************//
//*********************//
//*********************//

ParticleList::ParticleList(int Ratio, int x, int y) {
	srand(std::time(NULL));
	Start = new Particle(Ratio, x, y, 1);
	End = Start;
	Move = Start;
	End->ID = 1;
	Compare = Start;
}

void ParticleList::updateParticles() {
	getTime();
	Move = Start;
	while (Move->Next != nullptr) {
		Move->time = time;
		Move->draw();
		Move = Move->Next;
	}
	Move->time = time;
	End->draw();
	collisionDetector();
	std::cout << End->ID << std::endl;
}

void ParticleList::newParticle(int Ratio, int x, int y) {
	Move = new Particle(Ratio, x, y, End->ID + 1);
	End->Next = Move;
	End = Move;
}

void ParticleList::getTime() {
	static float timeRunning = 0;
	if (timeRunning == 0) {
		timeRunning = glutGet(GLUT_ELAPSED_TIME);
	}
	if (glutGet(GLUT_ELAPSED_TIME) - (timeRunning + 800 / 60) > 0) {
		time = (glutGet(GLUT_ELAPSED_TIME) - timeRunning) / 1000;
		timeRunning = glutGet(GLUT_ELAPSED_TIME);
	}
}

void ParticleList::collisionDetector() {
	if(Start->Next == nullptr){
		return;
	}
	bool past = false;
	Move = Start;
	float overlap = 0;
	Compare = Move->Next;
	float distance;
	int pastX, pastY;
	int fullRatio;
	while(Move->ID < End->ID) {
		Move->onCollision = false;
		Move = Move->Next;
	}
	End->onCollision = false;
	Move = Start;
	for (int i = 0; i < End->ID - 1; i++) {
		for (int j = i + 1; j < End->ID; j++) {
			fullRatio = Move->ratio + Compare->ratio;
			if ((abs(Move->posX - Compare->posX) <= fullRatio)) {
				if ((abs(Move->posY - Compare->posY) <= fullRatio)) {
					distance = sqrt((((Compare->posX - Move->posX) * (Compare->posX - Move->posX)) + ((Move->posY - Compare->posY) * (Move->posY - Compare->posY))));
					if (distance < fullRatio) {
						Move->onCollision = true;
						Compare->onCollision = true;
						overlap = abs((distance - Move->ratio - Compare->ratio) / (float)2);
						int POSX = Move->posX, POSY = Move->posY;
						float AllMass = Move->mass + Compare->mass;

						if (distance == 0) {
							Move->posX -= 1;
							Move->posY -= 1;
							Compare->posX += 1;
							Compare->posY += 1;
						}
						else {
							float VelX = overlap * abs(Compare->posX - Move->posX) / distance, VelY = overlap * abs(Compare->posY - Move->posY) / distance;

							if (Move->posX < Compare->posX) {
								Move->velocityX -= VelX * Compare->mass / AllMass;

								Compare->velocityX += VelX * Move->mass / AllMass;
							}
							else {
								Move->velocityX += VelX * Compare->mass / AllMass;

								Compare->velocityX -= VelX * Move->mass / AllMass;
							}

							if (Move->posY < Compare->posY) {
								Move->velocityY -= VelY * Compare->mass / AllMass;

								Compare->velocityY += VelY * Move->mass / AllMass;
							}
							else {
								Move->velocityY += VelY * Compare->mass / AllMass;

								Compare->velocityY -= VelY * Move->mass / AllMass;
							}
						}
						past = true;
					}
					if (distance <= fullRatio + .1) {
						Move->onCollision = true;
						Compare->onCollision = true;
					}
					else
						distance = 0;
				}
			}
			Compare = Compare->Next;
		}
		Move = Move->Next;
		Compare = Move->Next;
	}
}