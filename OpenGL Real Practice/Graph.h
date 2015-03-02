#pragma once

#include <vector>
#include <stack>
#include <list>
#include <iostream>

#include "SpriteAnimated.h"

struct Edge;
typedef std::vector<Edge> EdgeList;

class GraphNode {
public:
	GraphNode();
	GraphNode(int a_data);
	EdgeList edges;
	unsigned int number;
	int data, x, y;
	bool visited = false;
	float Gscore, Fscore;
	GraphNode* NLast;
};

struct Edge {
	GraphNode* startNode;
	GraphNode* endNode;
	float weight = 1;
};

class Graph {
	typedef std::vector<GraphNode*> NodeList;
public:
	Graph();

	void addNode(GraphNode* a_node);
	void removeNode(GraphNode* a_node);
	void setEdge(GraphNode* a_node1, GraphNode* a_node2, float a_weight);
	void printGraph();
	void resetVisited();

	static bool compareNodesG(const GraphNode* a_node1, const GraphNode* a_node2);
	static bool compareNodesF(const GraphNode* a_node1, const GraphNode* a_node2);

	bool SearchDFS(GraphNode* a_start, GraphNode* a_end);
	bool SearchDijkstra(GraphNode* a_start, GraphNode* a_end);
	bool SearchAStar(GraphNode* a_start, GraphNode* a_end);

	void drawGrid();
//private:
	int numOfNodes = 0;
	NodeList nodes;
	SpriteAnimated sprite;
};