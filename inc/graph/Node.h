#pragma once

#include <vector>

namespace troll {
namespace graph {
	template <typename index>
	class Node {
		Node(index ID, const std::vector<index> EdgeIDs) : 
		mID(ID),
		mEdgeIDs(EdgeIDs) {

		}

		virtual ~Node() {}

		index getID() const {
			return mID;
		}

		const std::vector<index>& getEdgeIDs() const {
			return mEdgeIDs;
		}

		private:
		index mID;
		std::vector<index> mEdgeIDs;
	};
}
}
