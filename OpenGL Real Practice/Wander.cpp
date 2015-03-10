#pragma once

#include "Steering Behavior.h"

glm::vec2 Wander::getForce() {
	//calculate wander
	glm::vec2 testRandom = glm::vec2((rand() % 200) - 100, (rand() % 200) - 100);
	if (testRandom.x < 1 && testRandom.x > -1) {
		testRandom.x = 1;
	}
	if (testRandom.y < 1 && testRandom.y > -1) {
		testRandom.y = 1;
	}
	glm::vec2 target = glm::normalize(testRandom);
	target *= radius;
	target += (glm::normalize(glm::vec2((rand() % 200) - 100, (rand() % 200) - 100)) * jitter);
	target = glm::normalize(target) * radius;
	//set wander final
	glm::vec2 ret = owner.position + (target + (owner.heading * distance));
	//seek final
	glm::vec2 V = glm::normalize(target - owner.position) * owner.speed;
	glm::vec2 Force = V - owner.velocity;
	return Force;
}