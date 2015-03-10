#pragma once

#include "Steering Behavior.h"

glm::vec2 Flee::getForce() {
	glm::vec2 V = glm::normalize(owner.position - target.position) * owner.speed;
	glm::vec2 Force = V - owner.velocity;
	return Force;
}