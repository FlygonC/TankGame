#pragma once

#include "SteeringBehavior.h"

glm::vec2 Avoid::getForce(Agent* a_owner) {
	glm::vec2 targetDest;
	if (glm::length(target->position - a_owner->position) <= radius) {
		targetDest -= target->position - a_owner->position;
		/*if (glm::length(target->position - a_owner->position) < glm::length(target->heading * target->speed)) {
			targetDest = glm::lerp(target->position, targetDest, (glm::length(target->position - a_owner->position) / glm::length(target->heading * target->speed)) - 0.1f);
		}*/
	}
	else {
		return targetDest;
	}

	glm::vec2 V = glm::normalize(targetDest) * a_owner->speed;
	glm::vec2 Force = V - a_owner->velocity;

	return Force;
}