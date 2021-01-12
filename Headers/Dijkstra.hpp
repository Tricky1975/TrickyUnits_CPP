// Lic:
// Headers/Dijkstra.hpp
// Dijkstra (header)
// version: 21.01.13
// Copyright (C) 2021 Jeroen P. Broks
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
#include <vector>
#include <map>

namespace TrickyUnits {

	typedef bool (*DijkstraPassible)(int x, int y); // DijkstraPassible;

	typedef struct DijkstraNode {
		int x = 0, y = 0, prevx = 0, prevy = 0;
		bool hasprev = false;
	}DijstraNode;


	class Dijkstra {
	private:
		std::vector<DijkstraNode> Nodes;
		std::vector<DijkstraNode> Queue;
		std::map <std::string, DijkstraNode> Work;
		bool EndReached = false;
		void NewNode(int x, int y, DijkstraPassible f,int sx,int sy, bool prev=false,int px=0,int py=0 );
		void QueueNode(int x, int y, bool prev = false, int px = 0, int py = 0);
		bool NodeExists(int x, int y);
	public:
		/// <summary>
		/// If set to true diagonal node checkes will be allowed. If set to false, they will be skipped.
		/// </summary>
		bool AllowDiagonal = false;
		/// <summary>
		/// Try to calcuate a route
		/// </summary>
		/// <param name="func">Dijkstra doesn't know how you set up your matrix. So you got to tell it!</param>
		/// <param name="startX"></param>
		/// <param name="startY"></param>
		/// <param name="endX"></param>
		/// <param name="endY"></param>
		void CalculatePath(DijkstraPassible func, int startX, int startY, int endX, int endY);

		/// <returns>Returns true if a path was succesfully created</returns>
		bool Success();

		/// <returns>Number of nodes</returns>
		int Length();

		DijkstraNode Node(int index);

	};
}