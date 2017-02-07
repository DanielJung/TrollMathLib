#pragma once

#include "IEdge.h"

namespace troll {
	namespace graph {
		template <typename index>
		class Edge : public IEdge<index> {
		public:
			Edge(index ID) :
				mID(ID) {

			}

			virtual ~Edge() {}

			index getID() const {
				return mID;
			}

		protected:
			index mID;
		};
	}
}
