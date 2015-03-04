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
				//Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) - 1], 1);
			}
			if (i < a_width - 1) {//edge to node East
				//Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) + 1], 1);
			}
			if (j > 0) {//edge to node north
				//Edge newEdge;
				returnGraph.setEdge(T, returnGraph.nodes[((j*a_width) + i) - a_width], 1);
			}
			if (j < a_height - 1) {//edge to node south
				//Edge newEdge;
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

	SpriteAnimated TileStamp;
	TileStamp.initializeSprite("gridtiles.png", 200, 100, 40, 40);
	TileStamp.makeBasicStructure(5, 1);
	TileStamp.playFrame(0);

	Grid.sprite = TileStamp;

	Grid.blockNode(Grid.getByPosition(19, 0));
	Grid.blockNode(Grid.getByPosition(18, 1));
	Grid.blockNode(Grid.getByPosition(17, 2));
	Grid.blockNode(Grid.getByPosition(16, 3));
	Grid.blockNode(Grid.getByPosition(15, 4));

	Grid.blockNode(Grid.getByPosition(14, 4));
	Grid.blockNode(Grid.getByPosition(13, 4));
	Grid.blockNode(Grid.getByPosition(12, 4));
	Grid.blockNode(Grid.getByPosition(11, 5));
	Grid.blockNode(Grid.getByPosition(10, 6));
	
	Grid.blockNode(Grid.getByPosition(13, 6));
	Grid.blockNode(Grid.getByPosition(12, 7));
	Grid.blockNode(Grid.getByPosition(11, 8));
	Grid.blockNode(Grid.getByPosition(10, 9));
	Grid.blockNode(Grid.getByPosition(9, 10));
	Grid.blockNode(Grid.getByPosition(8, 11));
	Grid.blockNode(Grid.getByPosition(7, 12));
	Grid.blockNode(Grid.getByPosition(6, 13));
	//Grid.blockNode(Grid.getByPosition(5, 14));
	Grid.blockNode(Grid.getByPosition(4, 15));
	Grid.blockNode(Grid.getByPosition(3, 16));
	Grid.blockNode(Grid.getByPosition(2, 17));
	Grid.blockNode(Grid.getByPosition(1, 18));
	Grid.blockNode(Grid.getByPosition(0, 19));

	Grid.blockNode(Grid.getByPosition(9, 9));
	Grid.blockNode(Grid.getByPosition(10, 10));

	Grid.blockNode(Grid.getByPosition(5, 15));
	Grid.blockNode(Grid.getByPosition(6, 15));
	Grid.blockNode(Grid.getByPosition(7, 15));
	Grid.blockNode(Grid.getByPosition(8, 15));
	Grid.blockNode(Grid.getByPosition(9, 15));
	Grid.blockNode(Grid.getByPosition(10, 15));
	Grid.blockNode(Grid.getByPosition(11, 15));
	Grid.blockNode(Grid.getByPosition(12, 15));
	Grid.blockNode(Grid.getByPosition(13, 15));
	Grid.blockNode(Grid.getByPosition(14, 15));
	Grid.blockNode(Grid.getByPosition(15, 15));
	Grid.blockNode(Grid.getByPosition(15, 14));
	Grid.blockNode(Grid.getByPosition(15, 13));
	Grid.blockNode(Grid.getByPosition(15, 12));
	Grid.blockNode(Grid.getByPosition(15, 11));

	Grid.blockNode(Grid.getByPosition(0, 5));
	Grid.blockNode(Grid.getByPosition(1, 5));
	Grid.blockNode(Grid.getByPosition(2, 5));
	Grid.blockNode(Grid.getByPosition(3, 5));
	Grid.blockNode(Grid.getByPosition(4, 5));
	Grid.blockNode(Grid.getByPosition(5, 5));
	Grid.blockNode(Grid.getByPosition(6, 5));
	
	Grid.blockNode(Grid.getByPosition(4, 14));
	Grid.blockNode(Grid.getByPosition(4, 13));
	Grid.blockNode(Grid.getByPosition(4, 12));
	Grid.blockNode(Grid.getByPosition(4, 11));
	Grid.blockNode(Grid.getByPosition(4, 10));
	Grid.blockNode(Grid.getByPosition(4, 9));
	Grid.blockNode(Grid.getByPosition(4, 8));

	Grid.SearchAStar(Grid.getByPosition(0, 0), Grid.getByPosition(19, 18), 1);

	//std::cout << Grid.raycast(Grid.getByPosition(0, 4), Grid.getByPosition(0, 3));

	//float timePass = 0;

	while (!glfwWindowShouldClose(root->window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		FDeltaTime = getDeltaTime();
		


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