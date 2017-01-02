#pragma once

#include <vector>
#include <map>

#include "INode.h"
#include "IEdge.h"
#include "../storage/COOMat.h"
#include "../storage/Vec.h"

namespace troll {
namespace graph {
	template<typename index>
	class Graph {
	public:
		
	private:
		storage::COOMat<index, index> mAdjacencyMatrix;
		storage::Vec<index, INode> mNodes;
		storage::Vec<index, IEdge> mEdges;
	};
}
}