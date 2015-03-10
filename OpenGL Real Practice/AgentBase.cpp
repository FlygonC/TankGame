#pragma once

#include "AgentBase.h"

Agent::Agent() {
	position = glm::vec2(0, 0);
	velocity = glm::vec2(1, 1);
	heading = glm::vec2(0, 0);
	speed = 200;

	sprite.initializeSprite("gridtiles.png", 100, 100, 20, 20);
	sprite.makeBasicStructure(5, 1);
	sprite.playFrame(3);
}

void Agent::Update(float FDelta) {
	/*if (velocity.length() > maxVelocity) {
		velocity = glm::normalize(velocity);
	}*/

	//velocity += behavior->getForce() * FDelta;

	if (velocity.x != 0 && velocity.y != 0) {
		heading = glm::normalize(velocity);
	}
	else {
		if (velocity.x < 0.1 && velocity.x > -0.1) {
			heading = glm::normalize(velocity);
			heading.x = 0;
		}
		if (velocity.y < 0.1 && velocity.y > -0.1) {
			heading = glm::normalize(velocity);
			heading.y = 0;
		}
	}
	position += (heading * speed) * FDelta;

	if (position.x > 800) {
		position.x -= 800;
	}
	if (position.x < 0) {
		position.x += 800;
	}
	if (position.y > 800) {
		position.y -= 800;
	}
	if (position.y < 0) {
		position.y += 800;
	}

	sprite.position = position;
	sprite.Draw();
}

/*glm::vec2 Agent::seek(glm::vec2 a_target) {
	glm::vec2 V = glm::normalize(a_target - position) * speed;
	glm::vec2 Force = V - velocity;
	return Force;
}
glm::vec2 Agent::flee(glm::vec2 a_target) {
	glm::vec2 V = glm::normalize(position - a_target) * speed;
	glm::vec2 Force = V - velocity;
	return Force;
}

glm::vec2 Agent::wander(float w_radius, float w_distance, float w_jitter) {
	glm::vec2 testRandom = glm::vec2((rand() % 200) - 100, (rand() % 200) - 100);
	if (testRandom.x < 1 && testRandom.x > -1) {
		testRandom.x = 1;
	}
	if (testRandom.y < 1 && testRandom.y > -1) {
		testRandom.y = 1;
	}
	glm::vec2 target = glm::normalize(testRandom);
	target *= w_radius;
	target += (glm::normalize(glm::vec2((rand() % 200) - 100, (rand() % 200) - 100)) * w_jitter);
	target = glm::normalize(target) * w_radius;
	//target += heading * w_distance;
	glm::vec2 ret = position + (target + (heading * w_distance));
	//velocity *= 0.5;
	return seek(ret);
}*/