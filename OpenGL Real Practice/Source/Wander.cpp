#pragma once

#include "SteeringBehavior.h"

glm::vec2 Wander::getForce(Agent* a_owner) {
	
	//calculate wander
	glm::vec2 testRandom = glm::vec2((rand() % 200) - 100, (rand() % 200) - 100);
	if (testRandom.x < 1 && testRandom.x > -1) {
		testRandom.x = 1;
	}
	if (testRandom.y < 1 && testRandom.y > -1) {
		testRandom.y = 1;
	}
	glm::vec2 w_target = glm::normalize(testRandom);
	w_target *= radius;

	testRandom = glm::vec2((rand() % 200) - 100, (rand() % 200) - 100);
	if (testRandom.x < 1 && testRandom.x > -1) {
		testRandom.x = 1;
	}
	if (testRandom.y < 1 && testRandom.y > -1) {
		testRandom.y = 1;
	}
	w_target += (glm::normalize(glm::vec2(testRandom)) * jitter);

	if (w_target.x < 0.1 && w_target.x > -0.1) {
		w_target.x = 0.1f;
	}
	if (w_target.y < 0.1 && w_target.y > -0.1) {
		w_target.y = 0.1f;
	}
	w_target = glm::normalize(w_target) * radius;

	//set wander final
	glm::vec2 ret = a_owner->position + (w_target + (a_owner->heading * distance));
	//seek final
	glm::vec2 V = glm::normalize(ret - a_owner->position) * a_owner->speed;
	glm::vec2 Force = V - a_owner->velocity;
	return Force;
	
	//return glm::vec2(0, 0);
}