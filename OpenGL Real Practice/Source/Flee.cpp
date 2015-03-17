#pragma once

#include "SteeringBehavior.h"

glm::vec2 Flee::getForce(Agent* a_owner) {
	glm::vec2 V = glm::normalize(a_owner->position - target->position) * a_owner->speed;
	glm::vec2 Force = V - a_owner->velocity;
	return Force;
	//return glm::vec2(0, 0);
}