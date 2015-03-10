#ifndef _STEERING_H_
#define _STEERING_H_

#include "AgentBase.h"

class SteeringBehavior {
public:
	Agent owner;

	virtual glm::vec2 getForce() = 0;
};


class Seek : public SteeringBehavior {
public:
	Agent target;

	glm::vec2 getForce();
};

class Flee : public SteeringBehavior {
public:
	Agent target;

	glm::vec2 getForce();
};

class Wander : public SteeringBehavior {
public:
	glm::vec2 target;
	float radius, jitter, distance;

	glm::vec2 getForce();
};

#endif