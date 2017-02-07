#pragma once

namespace troll {
	namespace graph {
		template <typename index>
		class IEdge {
		public:
			virtual index getID() const = 0;
		};
	}
}