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

Graph createGridGraph(int a_width, int a_height) {
	Graph returnGraph;
	for (int i = 0; i < a_width; i++) {
		for (int j = 0; j < a_height; j++) {
			GraphNode* newNode = new GraphNode(0);
			newNode->x = i;
			newNode->y = j;
			//newNode->data = 0;
			returnGraph.addNode(newNode);
		}
	}
	for (int j = 0; j < a_height; j++) {
		for (int i = 0; i < a_width; i++) {
			GraphNode* T = returnGraph.nodes[(j*a_width) + i];
			if (i > 0) {//edge to node west
				Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) - 1], 1);
			}
			if (i < a_width - 1) {//edge to node East
				Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) + 1], 1);
			}
			if (j > 0) {//edge to node north
				Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) - a_width], 1);
			}
			if (j < a_height - 1) {//edge to node south
				Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) + a_width], 1);
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
	
	Graph Grid = createGridGraph(20, 20);

	//Grid.printGraph();
	//Grid.SearchAStar(Grid.nodes[0], Grid.nodes[399]);

	//SpriteAnimated test;
	//test.initializeSprite("BombSprite.png", 100, 100, 80, 20);
	//test.makeBasicStructure(3, 1);
	//test.playFrame(0);

	SpriteAnimated TileStamp;
	TileStamp.initializeSprite("BombSprite.png", 100, 100, 40, 40);
	TileStamp.makeBasicStructure(3, 1);
	TileStamp.playFrame(0);

	while (!glfwWindowShouldClose(root->window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		FDeltaTime = getDeltaTime();
		if (FDeltaTime >= 0.1) {
			FDeltaTime = 0.1;
		}

		Grid.sprite.Draw();
		TileStamp.Draw();

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