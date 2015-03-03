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
	TileStamp.initializeSprite("gridtiles.png", 200, 100, 40, 40);
	TileStamp.makeBasicStructure(3, 1);
	TileStamp.playFrame(0);

	Grid.sprite = TileStamp;

	Grid.removeNode(Grid.getByPosition(0, 19));
	Grid.removeNode(Grid.getByPosition(1, 18));
	Grid.removeNode(Grid.getByPosition(2, 17));
	Grid.removeNode(Grid.getByPosition(3, 16));
	Grid.removeNode(Grid.getByPosition(4, 15));
	Grid.removeNode(Grid.getByPosition(5, 14));
	Grid.removeNode(Grid.getByPosition(6, 14));
	Grid.removeNode(Grid.getByPosition(7, 14));
	Grid.removeNode(Grid.getByPosition(8, 14));
	Grid.removeNode(Grid.getByPosition(9, 14));
	Grid.removeNode(Grid.getByPosition(10, 14));


	Grid.removeNode(Grid.getByPosition(5, 10));
	Grid.removeNode(Grid.getByPosition(6, 10));
	Grid.removeNode(Grid.getByPosition(7, 10));
	Grid.removeNode(Grid.getByPosition(8, 10));
	Grid.removeNode(Grid.getByPosition(9, 10));

	Grid.removeNode(Grid.getByPosition(5, 11));
	Grid.removeNode(Grid.getByPosition(5, 12));
	Grid.removeNode(Grid.getByPosition(5, 13));

	Grid.removeNode(Grid.getByPosition(7, 12));
	Grid.removeNode(Grid.getByPosition(8, 12));
	Grid.removeNode(Grid.getByPosition(9, 12));
	Grid.removeNode(Grid.getByPosition(10, 12));
	Grid.removeNode(Grid.getByPosition(11, 12));
	Grid.removeNode(Grid.getByPosition(12, 12));
	Grid.removeNode(Grid.getByPosition(13, 12));
	Grid.removeNode(Grid.getByPosition(14, 12));
	Grid.removeNode(Grid.getByPosition(15, 12));
	Grid.removeNode(Grid.getByPosition(16, 12));

	Grid.removeNode(Grid.getByPosition(0, 7));
	Grid.removeNode(Grid.getByPosition(1, 7));
	Grid.removeNode(Grid.getByPosition(2, 7));
	Grid.removeNode(Grid.getByPosition(3, 7));
	Grid.removeNode(Grid.getByPosition(4, 7));
	Grid.removeNode(Grid.getByPosition(5, 7));
	Grid.removeNode(Grid.getByPosition(6, 7));

	Grid.removeNode(Grid.getByPosition(8, 19));
	Grid.removeNode(Grid.getByPosition(8, 18));
	Grid.removeNode(Grid.getByPosition(8, 17));

	Grid.SearchAStar(Grid.getByPosition(3, 19), Grid.getByPosition(0, 11));

	while (!glfwWindowShouldClose(root->window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		FDeltaTime = getDeltaTime();
		if (FDeltaTime >= 0.1) {
			FDeltaTime = 0.1;
		}


		Grid.drawGrid();
		//Grid.sprite.Draw();
		//TileStamp.Draw();

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