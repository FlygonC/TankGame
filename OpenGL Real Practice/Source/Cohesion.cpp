#pragma once

#include "SteeringBehavior.h"

glm::vec2 Cohesion::getForce(Agent* a_owner) {
	glm::vec2 target = glm::vec2(0, 0);
	int sees = 0;
	for (int i = 0; i < hood.size(); i++) {
		if (glm::length(hood[i]->position - a_owner->position) < radius) {
			if (hood[i] != a_owner) {
				target += hood[i]->position - a_owner->position;
				sees += 1;
			}
		}
	}
	if (sees == 0) {
		return target;
	}

	target /= sees;

	glm::vec2 V = glm::normalize(target) * a_owner->speed;
	glm::vec2 Force = V - a_owner->velocity;

	return Force;
}

/*void Cohesion::getHood(Agent* a_owner, std::vector<Agent*> a_neighbors, float a_radius) {
	hood.clear();
	for (int i = 0; i < a_neighbors.size(); i++) {
		if (glm::length(a_neighbors[i]->position - a_owner->position) <= a_radius) {
			hood.push_back(a_neighbors[i]);
		}
	}
}*/