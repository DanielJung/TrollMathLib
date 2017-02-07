#pragma once

#include "INode.h"

namespace troll {
namespace graph {
	template <typename index>
	class Node : public INode<index> {
	public:
		Node(index ID) : 
			mID(ID) {

		}

		virtual ~Node() {}

		index getID() const {
			return mID;
		}

	protected:
		index mID;
	};
}
}
