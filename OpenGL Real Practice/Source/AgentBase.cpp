#pragma once

#include "AgentBase.h"

Agent::Agent() {
	position = glm::vec2(0, 0);
	velocity = glm::vec2(1, 1);
	heading = glm::vec2(0, 0);
	speed = 200;
	//behavior = NULL;

	sprite.initializeSprite("Resources\\gridtiles.png", 100, 100, 20, 20);
	sprite.makeBasicStructure(5, 1);
	sprite.playFrame(3);
}

void Agent::Update(float FDelta) {
	/*if (velocity.length() > maxVelocity) {
		velocity = glm::normalize(velocity);
	}*/
	/*if (behaviorComp[0] != NULL) {
		velocity += (behaviorComp[0]->getForce(this));
		//glm::vec2 out = behavior->getForce(this);
		//std::cout << out.x << "," << out.x << std::endl;
	}*/
	for (int i = 0; i < behaviorComp.size(); i++) {
		velocity += (behaviorComp[i]->getForce(this) / (behaviorComp[i]->weight + 1.f));
	}

	if (velocity.x < 0.1 && velocity.x > -0.1) {
		velocity.x = 0.1f;
	}
	if (velocity.y < 0.1 && velocity.y > -0.1) {
		velocity.y = 0.1f;
	}
	heading = glm::normalize(velocity);
	
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

void Agent::addBehavior(BEHAVE a_behavior) {
	SteeringBehavior* B;

	switch (a_behavior) {
	case SEEK:
		B = new Seek();
		break;
	case FLEE:
		B = new Flee();
		break;
	case WANDER:
		B = new Wander();
		break;
	case PERSUE:
		B = new Persue();
		break;
	case EVADE:
		B = new Evade();
		break;
	case SEPERATION:
		B = new Seperation();
		break;
	case COHESION:
		B = new Cohesion();
		break;
	case ALIGNMENT:
		B = new Alignment();
		break;
	case AVOID:
		B = new Avoid();
		break;
	}

	behaviorComp.push_back(B);
}

void Agent::addBehavior(BEHAVE a_behavior, Agent* t_target, float a_weight) {
	SteeringBehavior* B;

	switch (a_behavior) {
	case SEEK:
		B = new Seek();
		break;
	case FLEE:
		B = new Flee();
		break;
	case WANDER:
		B = new Wander();
		break;
	case PERSUE:
		B = new Persue();
		break;
	case EVADE:
		B = new Evade();
		break;
	case SEPERATION:
		B = new Seperation();
		break;
	case COHESION:
		B = new Cohesion();
		break;
	case ALIGNMENT:
		B = new Alignment();
		break;
	case AVOID:
		B = new Avoid();
		break;
	}

	behaviorComp.push_back(B);

	B->target = t_target;
	B->weight = a_weight;
}

void Agent::addBehavior(BEHAVE a_behavior, Agent* t_target, float w_radius, float a_weight) {
	SteeringBehavior* B;

	switch (a_behavior) {
	case SEEK:
		B = new Seek();
		break;
	case FLEE:
		B = new Flee();
		break;
	case WANDER:
		B = new Wander();
		break;
	case PERSUE:
		B = new Persue();
		break;
	case EVADE:
		B = new Evade();
		break;
	case SEPERATION:
		B = new Seperation();
		break;
	case COHESION:
		B = new Cohesion();
		break;
	case ALIGNMENT:
		B = new Alignment();
		break;
	case AVOID:
		B = new Avoid();
		break;
	}

	behaviorComp.push_back(B);

	B->target = t_target;
	B->radius = w_radius;
	B->weight = a_weight;
}

void Agent::addBehavior(BEHAVE a_behavior, float w_radius, float w_distance, float w_jitter, float a_weight) {
	SteeringBehavior* B;

	switch (a_behavior) {
	case SEEK:
		B = new Seek();
		break;
	case FLEE:
		B = new Flee();
		break;
	case WANDER:
		B = new Wander();
		break;
	case PERSUE:
		B = new Persue();
		break;
	case EVADE:
		B = new Evade();
		break;
	case SEPERATION:
		B = new Seperation();
		break;
	case COHESION:
		B = new Cohesion();
		break;
	case ALIGNMENT:
		B = new Alignment();
		break;
	case AVOID:
		B = new Avoid();
		break;
	}

	behaviorComp.push_back(B);

	B->radius = w_radius;
	B->distance = w_distance;
	B->jitter = w_jitter;
	B->weight = a_weight;
}

void Agent::addBehavior(BEHAVE a_behavior, float f_radius, std::vector<Agent*> a_neighborhood, float a_weight) {
	SteeringBehavior* B;

	switch (a_behavior) {
	case SEEK:
		B = new Seek();
		break;
	case FLEE:
		B = new Flee();
		break;
	case WANDER:
		B = new Wander();
		break;
	case PERSUE:
		B = new Persue();
		break;
	case EVADE:
		B = new Evade();
		break;
	case SEPERATION:
		B = new Seperation();
		break;
	case COHESION:
		B = new Cohesion();
		break;
	case ALIGNMENT:
		B = new Alignment();
		break;
	case AVOID:
		B = new Avoid();
		break;
	}

	behaviorComp.push_back(B);

	B->radius = f_radius;
	B->hood = a_neighborhood;
	B->weight = a_weight;
}