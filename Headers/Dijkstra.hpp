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