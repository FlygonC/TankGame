#ifndef _AGENT_H_
#define _AGENT_H_

#include "FrameWork.h"

#include "SpriteAnimated.h"
#include "Steering Behavior.h"

class Agent {
public:
	Agent();
	//~Agent();

	void Update(float FDelta);

	//glm::vec2 seek(glm::vec2 a_target);
	//glm::vec2 flee(glm::vec2 a_target);
	//glm::vec2 wander(float w_radius, float w_distance, float w_jitter);

	//SteeringBehavior* behavior;
	glm::vec2 position, velocity, heading;
	float speed;
	SpriteAnimated sprite;
};

#endif