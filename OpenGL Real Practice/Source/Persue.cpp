#pragma once

#include "SteeringBehavior.h"

glm::vec2 Persue::getForce(Agent* a_owner) {
	glm::vec2 targetDest = target->position + (target->heading * target->speed);
	//std::cout << findDistance(a_owner) / glm::length(target->heading * target->speed) << std::endl;
	if (glm::length(target->position - a_owner->position) < glm::length(target->heading * target->speed)) {
		targetDest = glm::lerp(target->position, targetDest, glm::length(target->position - a_owner->position) / glm::length(target->heading * target->speed));
	}
	//std::cout << (targetDest - target->position).x << "," << (targetDest - target->position).y << std::endl;
	glm::vec2 V = glm::normalize(targetDest - a_owner->position) * a_owner->speed;
	glm::vec2 Force = V - a_owner->velocity;
	return Force;
}

/*float Persue::findDistance(Agent* a_owner) {
	glm::vec2 vectorDist = target->position - a_owner->position;
	return abs(length(vectorDist));
}*/