#pragma once

#include "SteeringBehavior.h"

glm::vec2 Seek::getForce(Agent* a_owner) {
	glm::vec2 V = glm::normalize(target->position - a_owner->position) * a_owner->speed;
	glm::vec2 Force = V - a_owner->velocity;
	return Force;
	//return glm::vec2(0, 0);
}