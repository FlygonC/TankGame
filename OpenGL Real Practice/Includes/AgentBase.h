#ifndef _AGENT_H_
#define _AGENT_H_

#include "FrameWork.h"

#include "SpriteAnimated.h"
#include "SteeringBehavior.h"

class SteeringBehavior;
enum BEHAVE {SEEK, FLEE, WANDER, PERSUE, EVADE, SEPERATION, COHESION, ALIGNMENT, AVOID};
typedef std::vector<SteeringBehavior*> Behaviors;

class Agent {
public:
	Agent();
	//~Agent();

	void Update(float FDelta);

	//void changeBehavior(BEHAVE a_behavior);
	//void changeBehavior(BEHAVE a_behavior, Agent* t_target);
	//void changeBehavior(BEHAVE a_behavior, float w_radius, float w_distance, float w_jitter);
	void addBehavior(BEHAVE a_behavior);
	void addBehavior(BEHAVE a_behavior, Agent* t_target, float a_weight);
	void addBehavior(BEHAVE a_behavior, Agent* t_target, float w_radius, float a_weight);
	void addBehavior(BEHAVE a_behavior, float w_radius, float w_distance, float w_jitter, float a_weight);
	void addBehavior(BEHAVE a_behavior, float f_radius, std::vector<Agent*> a_neighborhood, float a_weight);
	void removeBehavior();

	Behaviors behaviorComp;
	glm::vec2 position, velocity, heading;
	float speed;
	SpriteAnimated sprite;
};

#endif