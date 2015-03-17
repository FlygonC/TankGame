#pragma once

#include "Graph.h"

Graph::Graph() {
	sprite.initializeSprite("Resources\\gridtiles.png", 100, 100, 40, 40);
	sprite.makeBasicStructure(5, 1);
	sprite.playFrame(0);
	sprite.fps = 0;
}

void Graph::addNode(GraphNode* a_node) {
	nodes.push_back(a_node);
	nodes.back()->number = numOfNodes;
	numOfNodes++;
}

void Graph::removeNode(GraphNode* a_node) {
	//Container for the node to delete
	NodeList::iterator deleteTarget = nodes.end();
	//Node loop \/\/
	for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
		//if iterator is equal to target node, set it to delete
		if ((*nodeIter) == a_node) {
			deleteTarget = nodeIter;
		}
		if ((*nodeIter)->number > a_node->number) {
			(*nodeIter)->number -= 1;
		}
		//Container for edge to delete
		EdgeList::iterator toDelete = (*nodeIter)->edges.end();
		//Edge loop \/
		for (EdgeList::iterator edgeIter = (*nodeIter)->edges.begin(); edgeIter != (*nodeIter)->edges.end(); edgeIter++) {
			//if iterator is equal to edge that points to target node, set it to remove
			if ((*edgeIter).endNode == a_node) {
				toDelete = edgeIter;
			}
		}// /\
		//Delete the edge, if one was found
		if (toDelete != (*nodeIter)->edges.end()) {
			(*nodeIter)->edges.erase(toDelete);
		}
	}// /\/\
	//Delete the node
	if (deleteTarget != nodes.end()) {
		nodes.erase(deleteTarget);
	}
	delete a_node;
	numOfNodes--;
}

void Graph::setEdge(GraphNode* a_node1, GraphNode* a_node2, float a_weight) {
	Edge newEdge;
	newEdge.startNode = a_node1;
	newEdge.endNode = a_node2;
	a_node1->edges.push_back(newEdge);
	a_node1->edges.back().weight = a_weight;
}

void Graph::printGraph() {
	for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
		std::cout << "Node " << (*nodeIter)->number << " = " << (*nodeIter)->data << std::endl;
		for (EdgeList::iterator edgeIter = (*nodeIter)->edges.begin(); edgeIter != (*nodeIter)->edges.end(); edgeIter++) {
			std::cout << "     Edge > " << (*edgeIter).endNode->number << "  W:" << (*edgeIter).weight << std::endl;
		}
	}
}

void Graph::resetVisited() {
	for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
		(*nodeIter)->visited = false;
		if ((*nodeIter)->locked == false) {
			(*nodeIter)->data = 0;
		}
		else {
			(*nodeIter)->data = 4;
		}
	}
}

GraphNode* Graph::getByPosition(int a_x, int a_y) {
	for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
		if ((*nodeIter)->x == a_x && (*nodeIter)->y == a_y) {
			return (*nodeIter);
		}
	}
}

bool Graph::compareNodesG(const GraphNode* a_node1, const GraphNode* a_node2) {
	return (a_node1->Gscore < a_node2->Gscore);
}

bool Graph::compareNodesF(const GraphNode* a_node1, const GraphNode* a_node2) {
	return (a_node1->Fscore < a_node2->Fscore);
}

bool Graph::SearchDFS(GraphNode* a_start, GraphNode* a_end) {
	std::stack<GraphNode*> NodeStack;
	NodeStack.push(a_start);
	while (!NodeStack.empty()) {
		GraphNode* Current = NodeStack.top();
		NodeStack.pop();
		if (Current->visited == true) {
			std::cout << "Passing Node " << Current->number << std::endl;
			continue;
		}
		std::cout << "Searching: " << Current->number;
		Current->visited = true;
		if (Current == a_end) {
			std::cout << " Found!" << std::endl;
			return true;
		}
		else {
			std::cout << std::endl;
			for (int i = 0; i < Current->edges.size(); i++) {
				NodeStack.push(Current->edges[i].endNode);
			}
		}
	}
	std::cout << "Could not find Node " << a_end->number << " from Node " << a_start->number << std::endl;
	return false;
}

bool Graph::SearchDijkstra(GraphNode* a_start, GraphNode* a_end) {
	std::list<GraphNode*> NodeQueue;
	for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
		(*nodeIter)->NLast = NULL;
		(*nodeIter)->Gscore = INFINITY;
	}
	NodeQueue.push_back(a_start);
	a_start->NLast = NodeQueue.back();
	a_start->Gscore = 0;
	int checkCount = 0;
	while (!NodeQueue.empty()) {
		GraphNode* Current = NodeQueue.front();
		NodeQueue.pop_front();
		if (Current->visited == true) {
			std::cout << "Passing Node " << Current->number << std::endl;
			continue;
		}
		checkCount++;
		std::cout << "Searching: " << Current->number << " (" << Current->x << "," << Current->y << ") From: " << Current->NLast->number << "  Score: " << Current->Gscore << "  Count: " << checkCount << std::endl;
		Current->visited = true;
		if (Current == a_end) {
			std::cout << "Done!" << std::endl;
			GraphNode* Retrace = a_end;
			while (Retrace != a_start) {
				std::cout << Retrace->number << " (" << Retrace->x << "," << Retrace->y << ") << " << std::endl;
				Retrace = Retrace->NLast;
			}
			std::cout << a_start->number << std::endl;
			resetVisited();
			return true;
		}
		for (int i = 0; i < Current->edges.size(); i++) {
			if (Current->edges[i].endNode->visited == false) {
				NodeQueue.push_back(Current->edges[i].endNode);
				Current->edges[i].endNode->Gscore = (Current->Gscore + Current->edges[i].weight);
				Current->edges[i].endNode->NLast = Current;
			}
		}
		NodeQueue.sort(compareNodesG);
	}
}

bool Graph::SearchAStar(GraphNode* a_start, GraphNode* a_end, float a_inadmissible) {
	std::list<GraphNode*> NodeQueue;
	for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
		(*nodeIter)->NLast = NULL;
		(*nodeIter)->Gscore = INFINITY;
		(*nodeIter)->Fscore = INFINITY;
	}
	NodeQueue.push_back(a_start);
	a_start->NLast = NodeQueue.back();
	a_start->Gscore = 0;
	a_start->Fscore = 0;
	int checkCount = 0;
	while (!NodeQueue.empty()) {
		GraphNode* Current = NodeQueue.front();
		NodeQueue.pop_front();
		if (Current->visited == true) {
			//std::cout << "Passing Node " << Current->number << std::endl;
			continue;
		}
		checkCount++;
		Current->data = 2;
		//std::cout << "Searching: " << Current->number << " (" << Current->x << "," << Current->y << ") From: " << Current->NLast->number << "  G: " << Current->Gscore << "  F: " << Current->Fscore << "  Count: " << checkCount << std::endl;
		Current->visited = true;
		if (Current == a_end) {
			//std::cout << "Done!" << std::endl;
			GraphNode* Retrace = a_end;
			//resetVisited();
			while (Retrace != a_start) {
				Retrace->data = 1;
				//std::cout << Retrace->number << " (" << Retrace->x << "," << Retrace->y << ") << " << std::endl;
				Retrace = Retrace->NLast;
			}
			//std::cout << a_start->number << std::endl;
			a_start->data = 3;
			a_end->data = 3;
			return true;
		}
		for (int i = 0; i < Current->edges.size(); i++) {
			if (Current->edges[i].endNode->visited == false && Current->edges[i].endNode->locked == false) {
				int Hx = 0;
				int Hy = 0;
				NodeQueue.push_front(Current->edges[i].endNode);
				Current->edges[i].endNode->Gscore = (Current->Gscore + Current->edges[i].weight);
				Hx = abs(a_end->x - Current->edges[i].endNode->x);
				Hy = abs(a_end->y - Current->edges[i].endNode->y);
				Current->edges[i].endNode->Fscore = Current->edges[i].endNode->Gscore + ((Hx + Hy) * (a_inadmissible + 1));
				Current->edges[i].endNode->NLast = Current;
			}
		}
		NodeQueue.sort(compareNodesF);
	}
}

bool Graph::SearchAStarSmooth(GraphNode* a_start, GraphNode* a_end, float a_inadmissible) {
	std::list<GraphNode*> NodeQueue;
	for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
		(*nodeIter)->NLast = NULL;
		(*nodeIter)->Gscore = INFINITY;
		(*nodeIter)->Fscore = INFINITY;
	}
	NodeQueue.push_back(a_start);
	a_start->NLast = NodeQueue.back();
	a_start->Gscore = 0;
	a_start->Fscore = 0;
	int checkCount = 0;
	while (!NodeQueue.empty()) {
		GraphNode* Current = NodeQueue.front();
		NodeQueue.pop_front();
		if (Current->visited == true) {
			//std::cout << "Passing Node " << Current->number << std::endl;
			continue;
		}
		checkCount++;
		//Current->data = 2;
		//std::cout << "Searching: " << Current->number << " (" << Current->x << "," << Current->y << ") From: " << Current->NLast->number << "  G: " << Current->Gscore << "  F: " << Current->Fscore << "  Count: " << checkCount << std::endl;
		Current->visited = true;
		if (Current == a_end) {
			//std::cout << "Done!" << std::endl;
			GraphNode* Retrace = a_end;
			GraphNode* RetraceSmooth = a_end;
			//resetVisited();
			while (Retrace != a_start) {
				if (raycast(Retrace->NLast, RetraceSmooth)) {
					Retrace->data = 2;
				}
				else {
					Retrace->data = 1;
					RetraceSmooth = Retrace;
				}
				Retrace = Retrace->NLast;
			}
			//std::cout << a_start->number << std::endl;
			a_start->data = 3;
			a_end->data = 3;
			return true;
		}
		for (int i = 0; i < Current->edges.size(); i++) {
			if (Current->edges[i].endNode->visited == false && Current->edges[i].endNode->locked == false) {
				int Hx = 0;
				int Hy = 0;
				NodeQueue.push_front(Current->edges[i].endNode);
				Current->edges[i].endNode->Gscore = (Current->Gscore + Current->edges[i].weight);
				Hx = abs(a_end->x - Current->edges[i].endNode->x);
				Hy = abs(a_end->y - Current->edges[i].endNode->y);
				Current->edges[i].endNode->Fscore = Current->edges[i].endNode->Gscore + ((Hx + Hy) * (a_inadmissible + 1));
				Current->edges[i].endNode->NLast = Current;
			}
		}
		NodeQueue.sort(compareNodesF);
	}
}

bool Graph::SearchThetaStar(GraphNode* a_start, GraphNode* a_end, float a_inadmissible) {
	std::list<GraphNode*> NodeQueue;
	for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
		(*nodeIter)->NLast = NULL;
		(*nodeIter)->Gscore = INFINITY;
		//(*nodeIter)->Fscore = INFINITY;
	}
	NodeQueue.push_back(a_start);
	a_start->NLast = NodeQueue.back();
	a_start->Gscore = 0;
	a_start->Fscore = 0;
	int checkCount = 0;
	while (!NodeQueue.empty()) {
		GraphNode* Current = NodeQueue.front();
		NodeQueue.pop_front();
		if (Current->visited == true) {
			//std::cout << "Passing Node " << Current->number << std::endl;
			continue;
		}
		checkCount++;
		Current->data = 2;
		//std::cout << "Searching: " << Current->number << " (" << Current->x << "," << Current->y << ") From: " << Current->NLast->number << "  G: " << Current->Gscore << "  F: " << Current->Fscore << "  Count: " << checkCount << std::endl;
		Current->visited = true;
		if (Current == a_end) {
			//std::cout << "Done!" << std::endl;
			GraphNode* Retrace = a_end;
			//resetVisited();
			while (Retrace != a_start) {
				Retrace->data = 1;
				std::cout << Retrace->number << " (" << Retrace->x << "," << Retrace->y << ") << " << std::endl;
				Retrace = Retrace->NLast;
			}
			//std::cout << a_start->number << std::endl;
			a_start->data = 3;
			a_end->data = 3;
			return true;
		}
		for (int i = 0; i < Current->edges.size(); i++) {
			if (Current->edges[i].endNode->visited == false) {
				int Hx = 0;
				int Hy = 0;
				NodeQueue.push_back(Current->edges[i].endNode);
				Current->edges[i].endNode->Gscore = (Current->Gscore + Current->edges[i].weight);
				Hx = abs(a_end->x - Current->edges[i].endNode->x);
				Hy = abs(a_end->y - Current->edges[i].endNode->y);
				Current->edges[i].endNode->Fscore = Current->edges[i].endNode->Gscore + ((Hx + Hy) * (a_inadmissible + 1));
				if (raycast(Current->NLast, Current->edges[i].endNode)) {
					Current->edges[i].endNode->NLast = Current->NLast;
				}
				else {
					Current->edges[i].endNode->NLast = Current;
				}
			}
		}
		NodeQueue.sort(compareNodesF);
	}
}

void Graph::drawGrid() {
	for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
		sprite.position = glm::vec2(((*nodeIter)->x * sprite.width) + sprite.width / 2, ((*nodeIter)->y * sprite.height) + sprite.height/2);
		sprite.playFrame((*nodeIter)->data);
		sprite.Draw();
	}
}

void Graph::blockNode(GraphNode* a_target) {
	a_target->locked = true;
	a_target->data = 4;
}

bool Graph::raycast(GraphNode* a_start, GraphNode* a_target) {
	bool temp = true;
	glm::vec2 startpos = glm::vec2((a_start->x * sprite.width) + sprite.width / 2, (a_start->y * sprite.height) + sprite.height / 2);
	glm::vec2 targetpos = glm::vec2((a_target->x * sprite.width) + sprite.width / 2, (a_target->y * sprite.height) + sprite.height / 2);
	for (int i = 0; i < 100; i++) {
		for (NodeList::iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
			if ((*nodeIter)->data == 4) {
				glm::vec2 lerpPos = glm::lerp(startpos, targetpos, i*0.01f);
				glm::vec2 bottomleft = glm::vec2(((*nodeIter)->x * sprite.width), ((*nodeIter)->y * sprite.height));
				glm::vec2 topright = glm::vec2(((*nodeIter)->x * sprite.width) + sprite.width, ((*nodeIter)->y * sprite.height) + sprite.height);
				if (lerpPos.x >= bottomleft.x && lerpPos.x <= topright.x &&
					lerpPos.y >= bottomleft.y && lerpPos.y <= topright.y) {
					temp = false;
				}
			}
		}
	}
	return temp;
}