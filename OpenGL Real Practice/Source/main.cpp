#include "FrameWork.h"
#include "Sprite.h"
#include "SpriteAnimated.h"
#include "SpriteString.h"
#include "Quad.h"

#include <iostream>
#include <time.h>
#include <cstring>
#include <sstream>

#include "Graph.h"
#include "AgentBase.h"

Graph createGridGraph(int a_width, int a_height, float a_weight) {
	Graph returnGraph;
	for (int i = 0; i < a_width; i++) {
		for (int j = 0; j < a_height; j++) {
			GraphNode* newNode = new GraphNode(0);
			newNode->x = j;
			newNode->y = i;
			//newNode->data = 0;
			returnGraph.addNode(newNode);
		}
	}
	for (int j = 0; j < a_height; j++) {
		for (int i = 0; i < a_width; i++) {
			GraphNode* T = returnGraph.nodes[(j*a_width) + i];
			if (i > 0) {//edge to node west
				//Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) - 1], a_weight);
			}
			if (i < a_width - 1) {//edge to node East
				//Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) + 1], a_weight);
			}
			if (j > 0) {//edge to node north
				//Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) - a_width], a_weight);
			}
			if (j < a_height - 1) {//edge to node south
				//Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) + a_width], a_weight);
			}
		}
	}
	return returnGraph;
}


int main() {
	
	FrameWork::screenHeight = 800;
	FrameWork::screenWidth = 800;
	FrameWork* root = new FrameWork();
	float FDeltaTime = getDeltaTime();
	srand(time(NULL));
	
	Graph Grid = Graph();
	//Graph Justin = Graph();
	Grid = createGridGraph(20, 20, 1);

	

	Grid.SearchAStar(Grid.getByPosition(0, 0), Grid.getByPosition(19, 19), 0);

	//std::cout << Grid.raycast(Grid.getByPosition(0, 4), Grid.getByPosition(0, 3));

	//float timePass = 0;

	Agent testAgent1;
	Agent testAgent2;
	testAgent2.sprite.playFrame(2);

	//testAgent1.addBehavior(PERSUE, &testAgent2, 0);

	testAgent2.addBehavior(WANDER, 50, 200, 0, 0);
	testAgent2.position.y = 400;
	testAgent2.position.x = 400;
	testAgent2.speed = 220;


	const int crowdSize = 150;
	std::vector<Agent*> crowd;
	for (int i = 0; i < crowdSize; i++) {
		Agent* A = new Agent();
		A->sprite.playFrame(1);
		A->position.x = rand() % 800;
		A->position.y = rand() % 800;
		A->velocity.x = (rand() % 100) - 50;
		A->velocity.y = (rand() % 100) - 50;
		//A->addBehavior(WANDER, 50, 200, 0);
		crowd.push_back(A);
	}
	for (int i = 0; i < crowd.size(); i++) {
		crowd[i]->addBehavior(SEPERATION, 20, crowd, 10);
		crowd[i]->addBehavior(COHESION, 100, crowd, 60);
		crowd[i]->addBehavior(ALIGNMENT, 40, crowd, 60);
		crowd[i]->addBehavior(WANDER, 50, 200, 20, 130);
		crowd[i]->addBehavior(AVOID, &testAgent2, 50, 5);
		crowd[i]->addBehavior(AVOID, &testAgent1, 50, 5);
		crowd[i]->speed = 200;

	}

	testAgent1.addBehavior(COHESION, 500, crowd, 100);

	double mousex, mousey;

	GraphNode* startNode = Grid.getByPosition(0, 0);
	GraphNode* targetNode = Grid.getByPosition(19, 19);

	while (!glfwWindowShouldClose(root->window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		FDeltaTime = getDeltaTime();
		glfwGetCursorPos(FrameWork::window, &mousex, &mousey);
		mousey *= -1;
		mousey += FrameWork::screenHeight;

		/*for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (mousex < (Grid.nodes[(j * 20) + i]->x * 40) + 40 && mousex > (Grid.nodes[(j * 20) + i]->x * 40) - 0 &&
					mousey < (Grid.nodes[(j * 20) + i]->y * 40) + 40 && mousey > (Grid.nodes[(j * 20) + i]->y * 40) - 0) {
					if (glfwGetMouseButton(root->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
						targetNode = Grid.nodes[(j * 20) + i];
						Grid.resetVisited();
						Grid.SearchAStarSmooth(startNode, targetNode, 0);
					}
					if (glfwGetMouseButton(root->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
						startNode = Grid.nodes[(j * 20) + i];
						Grid.resetVisited();
						Grid.nodes[(j * 20) + i]->data = 3;
					}
					if (glfwGetKey(root->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
						Grid.blockNode(Grid.nodes[(j * 20) + i]);
					}
				}
			}
		}

		Grid.drawGrid();*/

		for (int i = 0; i < crowd.size(); i++) {
			crowd[i]->Update(FDeltaTime);
		}

		testAgent1.Update(FDeltaTime);
		testAgent2.Update(FDeltaTime);

		resetTime();

		if (glfwGetKey(root->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(root->window, GL_TRUE);
		}
		glfwSwapBuffers(root->window);
		glfwPollEvents();
	}
	delete root;
	//glfwTerminate();
	return 0;
}