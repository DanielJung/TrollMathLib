#pragma once

#include <vector>

#include "INode.h"
#include "IEdge.h"
#include "../storage/COOMat.h"
#include "../storage/Vec.h"

namespace troll {
namespace graph {
	template<typename index>
	class Graph {
	public:
		Graph(const storage::COOMat<index, index>& AdjacencyMatrix, const storage::Vec<index, INode<index>*>& Nodes, const storage::Vec<index, IEdge<index>*>& Edges) :
			mAdjacencyMatrix(AdjacencyMatrix),
			mNodes(Nodes),
			mEdges(Edges) {

		}

		virtual ~Graph() {}

		const storage::Vec<index, INode<index>*> getNodes() const {
			return mNodes;
		}

		const storage::Vec<index, IEdge<index>*> getEdges() const {
			return mEdges;
		}

		const INode<index>* getNode(index id) const {
			for (index i = 0; i < mNodes.getSize(); ++i) {
				if (id == mNodes.at(i)->getID()) {
					return mNodes.at(i);
				}
			}
			throw std::invalid_argument("Error Graph: Node not found");
		}

		const IEdge<index>* getEdge(index id) const {
			for (index i = 0; i < mEdges.getSize(); ++i) {
				if (id == mEdges.at(i)->getID()) {
					return mEdges.at(i);
				}
			}
			throw std::invalid_argument("Error Graph: Edge not found");
		}
	private:
		storage::COOMat<index, index> mAdjacencyMatrix;
		storage::Vec<index, INode<index>*> mNodes;
		storage::Vec<index, IEdge<index>*> mEdges;
	};
}
}