// Lic:
// Source/Dijkstra.cpp
// Dijkstra Pathfindder
// version: 20.09.01
// Copyright (C) 2020 Jeroen P. Broks
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
// EndLic
#include <map>
#include <string>
#include <iostream>
#include "..\Headers\Dijkstra.hpp"


#undef Dijkstra_Stack_Debug
#undef Dijkstra_Result_Debug

using namespace TrickyUnits;

#ifdef Dijkstra_Stack_Debug
int stacked = 0;
#endif

void TrickyUnits::Dijkstra::NewNode(int x, int y, DijkstraPassible f, int sx, int sy, bool prev, int px, int py) {
#ifdef Dijkstra_Stack_Debug
	stacked++;
	std::cout << "Stacking up: " << stacked << "\t("<<px<<","<<py<<") => ("<<x<<","<<y<<")   hasprev:"<<prev<<";    Start:("<<sx<<","<<sy<<")\n";
	if (EndReached) {
#ifdef Dijkstra_Stack_Debug
		stacked--;
		std::cout << "Stacking down: " << stacked << "\tDestination reached\n";
#endif
		return;
	}
#endif
	if (NodeExists(x, y)) {
#ifdef Dijkstra_Stack_Debug
		stacked--;
		std::cout << "Stacking down: " << stacked << "\tNode (" << x << "," << y << ") exists\n";
#endif
		return;
	}
	//|| (!f(x, y))
	if (!f(x,y)) {
#ifdef Dijkstra_Stack_Debug
		stacked--;
		std::cout << "Stacking down: " << stacked << "\tNode (" << x << "," << y << ") blocked\n";
#endif
		return;
	}
	Work[std::to_string(x) + "," + std::to_string(y)] = { x, y, px, py, prev };
#ifdef Dijkstra_Result_Debug
	auto& DBGW = Work[std::to_string(x) + "," + std::to_string(y)];
	std::cout << "Created: (" << DBGW.x << "," << DBGW.y << ")  Prev: (" << DBGW.prevx << "," << DBGW.prevy << ")   hasprev=" << DBGW.hasprev << "\n";
#endif
	EndReached = EndReached || (x == sx && y == sy);
	if (EndReached) { 
#ifdef Dijkstra_Stack_Debug
		stacked--;
		std::cout << "Stacking down: " << stacked << "\nI FOUND IT!\a\n";
#endif

		return; 
	}
	/*
	NewNode(x - 1, y, f, sx, sy, true, x, y); // Left
	NewNode(x + 1, y, f, sx, sy, true, x, y); // Right
	NewNode(x, y - 1, f, sx, sy, true, x, y); // Up
	NewNode(x, y + 1, f, sx, sy, true, x, y); // Down
	//*/
	QueueNode(x - 1, y, true, x, y);
	QueueNode(x + 1, y, true, x, y);
	QueueNode(x , y-1, true, x, y);
	QueueNode(x , y+1, true, x, y);
	if (AllowDiagonal) {
		/*
		NewNode(x - 1, y - 1, f, sx, sy, true, x, y); // Up - Left
		NewNode(x - 1, y + 1, f, sx, sy, true, x, y); // Down - Left
		NewNode(x + 1, y - 1, f, sx, sy, true, x, y); // Up - Right
		NewNode(x + 1, y + 1, f, sx, sy, true, x, y); // Down - Right
		//*/
		QueueNode(x - 1, y + 1, true, x, y);
		QueueNode(x - 1, y - 1, true, x, y);
		QueueNode(x + 1, y - 1, true, x, y);
		QueueNode(x - 1, y + 1, true, x, y);
	}
#ifdef Dijkstra_Stack_Debug
	stacked--;
	std::cout << "Stacking down: " << stacked << "\nEnd of route\n";
#endif

}

void TrickyUnits::Dijkstra::QueueNode(int x, int y, bool prev, int px, int py) {
	Queue.push_back({ x,y,px,py,prev });
}

bool TrickyUnits::Dijkstra::NodeExists(int x, int y) {
	return Work.count(std::to_string(x) + "," + std::to_string(y));
}

void TrickyUnits::Dijkstra::CalculatePath(DijkstraPassible func, int startX, int startY, int endX, int endY) {
	Nodes.clear();
	Work.clear();
	Queue.clear();
	EndReached = false;	
	NewNode(endX, endY, func, startX, startY); // Yup working from the end to the start is the easier way to do this!
	while ((!EndReached) && Queue.size()) {
		auto workqueue = Queue;
		Queue.clear();
		for (auto& N : workqueue) NewNode(N.x, N.y, func, startX, startY, true, N.prevx, N.prevy);
	}
#ifdef Dijkstra_Result_Debug
	for (auto& DBG : Work) std::cout << "CHECK WORK[\"" << DBG.first << "\"] = { x = " << DBG.second.x << ", y = " << DBG.second.y << "; HasPrev = "<<DBG.second.hasprev<<"} \n";
#endif
	for (
		auto& Node = Work[std::to_string(startX) + "," + std::to_string(startY)];
		(Work[std::to_string(Node.x) + "," + std::to_string(Node.y)].hasprev); // || (Work[std::to_string(Node.prevx) + "," + std::to_string(Node.prevy)].x != endX && Work[std::to_string(Node.prevx) + "," + std::to_string(Node.prevy)].y != endY);
		Node = Work[std::to_string(Node.prevx) + "," + std::to_string(Node.prevy)]
		) {
#ifdef Dijkstra_Result_Debug
		std::cout << "PUSH WORK[\"" << (std::to_string(Node.x) + "," + std::to_string(Node.y)) << "\"] = { x = " << Node.x << ", y = " << Node.y << "; HasPrev = " << Node.hasprev << "; prevX = "<<Node.prevx<<"; prevY="<<Node.prevy<<"} \n";
#endif

		Nodes.push_back(Node);
	}
	Nodes.push_back(Work[std::to_string(endX) + "," + std::to_string(endY)]);
	Work.clear(); // No more need to keep all that crap!
}

bool TrickyUnits::Dijkstra::Success() {
	return EndReached;
}

int TrickyUnits::Dijkstra::Length() {
	return Nodes.size();
}

DijkstraNode TrickyUnits::Dijkstra::Node(int index) {
	DijkstraNode N;
	if (index < 0 || index >= Nodes.size()) {
		std::cout << "\x7Node index out of bounds! Index = " << index << "; Number Of Nodes = " << Nodes.size() << "\n";
	} else {
		N = Nodes[index];
	}
	return N;
}