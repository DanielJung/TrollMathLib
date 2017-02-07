#pragma once

namespace troll {
namespace graph {
	template <typename index>
	class INode {
	public:
		virtual index getID() const = 0;
	};
}
}