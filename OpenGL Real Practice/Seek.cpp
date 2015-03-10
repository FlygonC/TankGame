#pragma once

#include "Steering Behavior.h"

glm::vec2 Seek::getForce() {
	glm::vec2 V = glm::normalize(target.position - owner.position) * owner.speed;
	glm::vec2 Force = V - owner.velocity;
	return Force;
}