#pragma once

#include <graph\Node.h>
#include <environment\Edge2D.h>
#include <environment\IEnvironment.h>
#include <vector>

namespace tf {
	namespace env{
		class Node2D : public troll::graph::Node<unsigned int> {
		public:
			Node2D(unsigned int ID, const std::vector<unsigned int> InEdgeIDs, const std::vector<unsigned int> OutEdgeIDs);
			virtual ~Node2D();

			void InitPointers(const IEnvironment& Environment);

			const std::vector<unsigned int> getInEdgeIDs() const;
			const std::vector<unsigned int> getOutEdgeIDs() const;
			
		private:
			std::vector<unsigned int> mInEdgeIDs;
			std::vector<unsigned int> mOutEdgeIDs;

			std::vector<Edge2D*> mInEdges;
			std::vector<Edge2D*> mOutEdges;
		};
	}
}