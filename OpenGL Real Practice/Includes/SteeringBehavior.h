#ifndef _STEERING_H_
#define _STEERING_H_

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm\gtx\compatibility.hpp"

#include "AgentBase.h"
class Agent;

class SteeringBehavior {
public:
	Agent* target = NULL;
	float radius, jitter, distance, weight = 0;
	std::vector<Agent*> hood;
	virtual glm::vec2 getForce(Agent* a_owner) = 0;
};


class Seek : public SteeringBehavior {
public:
	glm::vec2 getForce(Agent* a_owner);
};

class Flee : public SteeringBehavior {
public:
	glm::vec2 getForce(Agent* a_owner);
};

class Wander : public SteeringBehavior {
public:
	glm::vec2 w_target;
	glm::vec2 getForce(Agent* a_owner);
};

class Persue : public SteeringBehavior {
public:
	glm::vec2 getForce(Agent* a_owner);
private:
	//float findDistance(Agent* a_owner);
};

class Evade : public SteeringBehavior {
public:
	glm::vec2 getForce(Agent* a_owner);
private:
	//float findDistance(Agent* a_owner);
};

class Avoid : public SteeringBehavior {
public:
	glm::vec2 getForce(Agent* a_owner);
private:
	//float findDistance(Agent* a_owner);
};

//Flock behaviors ###
class Seperation : public SteeringBehavior {
public:
	glm::vec2 getForce(Agent* a_owner);
private:
	//void getHood(Agent* a_owner, std::vector<Agent*> a_neighbors, float a_radius);
};

class Alignment : public SteeringBehavior {
public:
	glm::vec2 getForce(Agent* a_owner);
private:
	//void getHood(Agent* a_owner, std::vector<Agent*> a_neighbors, float a_radius);
};

class Cohesion : public SteeringBehavior {
public:
	glm::vec2 getForce(Agent* a_owner);
private:
	//void getHood(Agent* a_owner, std::vector<Agent*> a_neighbors, float a_radius);
};

#endif