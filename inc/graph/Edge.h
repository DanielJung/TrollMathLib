#pragma once

namespace troll{
namespace graph {
	template<typename index>
	class Edge {
		public:
		Edge(index ID, index SourceID, index TargetID) : 
			mID(ID),
			mSourceID(SourceID) {

		}

		virtual ~Edge() {}

		index getID() const {
			return mID;
		}

		index getSourceID() const {
			return mSourceID;
		}

		private:
		index mID;
		index mSourceID;
	}
}
}