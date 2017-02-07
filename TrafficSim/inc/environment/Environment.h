#pragma once

#include <string>
#include <vector>
#include <map>

#include <environment\IEnvironment.h>
#include <environment\Edge2D.h>
#include <environment\Vertex2D.h>
#include <environment\visual\SFMLNode.h>

namespace tf {
	namespace env {
		class Environment : public IEnvironment {
		public:
			Environment(const std::string& FileName);
			virtual ~Environment();

			const std::string& getName() const;
			double getVersion() const;

			Vertex2D* getVertex(unsigned int ID) const;
			const std::vector<Vertex2D*> getVertices(const std::vector<unsigned int>& IDs) const;
			std::vector<Vertex2D*> getAllVertices() const;

			Edge2D* getEdge(unsigned int ID) const;
			const std::vector<Edge2D*> getEdges(const std::vector<unsigned int>& IDs) const;
			const std::vector<Edge2D*> getAllEdges() const;

			Node2D* getNode(unsigned int ID) const;
			const std::vector<Node2D*> getNodes(const std::vector<unsigned int>& IDs) const;
			const std::vector<Node2D*> getAllNodes() const;
		private:
			std::string mName;
			double mVersion;

			std::vector<Vertex2D> mVertices;
			std::vector<Edge2D> mEdges;
			std::vector<visual::SFMLNode> mNodes;

			std::map<unsigned int, Vertex2D*> mVertexIndex;
			std::map<unsigned int, Edge2D*> mEdgeIndex;
			std::map<unsigned int, Node2D*> mNodeIndex;
		};
	}
}