#ifndef _FLOCK_H_
#define _FLOCK_H_

#include "FrameWork.h"

#include "SpriteAnimated.h"
#include "AgentBase.h"
#include "SteeringBehavior.h"

/*class BOID {
public:
	//SteeringBehavior* behavior;
	glm::vec2 position, velocity, heading;
	float speed;
	//SpriteAnimated sprite;

	BOID();
	void Update(float FDelta);
};*/

typedef std::vector<Agent*> flockList;
class Flock {
public:
	flockList boids;
	float commonRadius;

	Flock();
	Flock(int a_numOfBoids, float a_commonRadius);
	void Update();
};

#endif