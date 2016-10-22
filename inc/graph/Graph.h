#pragma once

#include <vector>
#include <map>

#include "Node.h"
#include "Edge.h"

namespace troll {
namespace graph {
	template<typename index>
	class Graph {
		public:
		Graph() {

		}

		virtual ~Graph() {}

		const Node<index>* getNode(index ID) const {
			return mNodeIndex[ID];
		}

		const Edge<index>* getEdge(index ID) const {
			return mEdgeIndex[ID];
		}


		private:
		std::map<index, Node<index>*> mNodeIndex;
		std::map<index, Edge<index>*> mEdgeIndex;
		std::vector<Node<index> > mNodes;
		std::vector<Edge<index> > mEdges;
	};
}
}