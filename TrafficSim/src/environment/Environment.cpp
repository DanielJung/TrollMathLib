#include <environment/Environment.h>

#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <rapidjson\document.h>

using namespace std;
using namespace tf;
using namespace tf::env;
using namespace rapidjson;

Environment::Environment(const std::string& FileName) {
	ifstream File(FileName.c_str(), ios::in);
	assert(File.is_open());

	stringstream Buffer;
	Buffer << File.rdbuf();

	File.close();

	Document JsonDocument;
	JsonDocument.Parse(Buffer.str().c_str());

	assert(JsonDocument.IsObject());

	assert(JsonDocument.HasMember("name"));
	assert(JsonDocument["name"].IsString());
	mName = JsonDocument["name"].GetString();

	assert(JsonDocument.HasMember("version"));
	assert(JsonDocument["version"].IsDouble());
	mVersion = JsonDocument["version"].GetDouble();

	assert(JsonDocument.HasMember("vertices"));
	assert(JsonDocument["vertices"].IsArray());
	const Value& VertexArray = JsonDocument["vertices"];
	for (SizeType i = 0; i < VertexArray.Size(); ++i) {
		assert(VertexArray[i].IsObject());
		auto& JsonVertex = VertexArray[i];

		assert(JsonVertex.HasMember("id"));
		assert(JsonVertex["id"].IsUint());

		assert(JsonVertex.HasMember("x"));
		assert(JsonVertex["x"].IsDouble());

		assert(JsonVertex.HasMember("y"));
		assert(JsonVertex["y"].IsDouble());

		mVertices.push_back(Vertex2D(JsonVertex["id"].GetUint(), JsonVertex["x"].GetDouble(), JsonVertex["y"].GetDouble()));
		mVertexIndex.insert(std::pair<unsigned int, Vertex2D*>(mVertices[mVertices.size() - 1].getID(), &mVertices[mVertices.size() - 1]));
	}


	assert(JsonDocument.HasMember("edges"));
	assert(JsonDocument["edges"].IsArray());
	const Value& EdgeArray = JsonDocument["edges"];
	for (SizeType i = 0; i < EdgeArray.Size(); ++i) {
		assert(EdgeArray[i].IsObject());

		auto& JsonEdge = EdgeArray[i];

		assert(JsonEdge.HasMember("id"));
		assert(JsonEdge["id"].IsUint());

		assert(JsonEdge.HasMember("vertices"));
		assert(JsonEdge["vertices"].IsArray());

		std::vector<unsigned int> VertexIDs;
		const Value& VertexArray = JsonEdge["vertices"];
		for (SizeType j = 0; j < VertexArray.Size(); ++j) {
			assert(VertexArray[j].IsUint());
			VertexIDs.push_back(VertexArray[j].GetUint());
		}

		mEdges.push_back(Edge2D(JsonEdge["id"].GetUint(), VertexIDs));
		mEdgeIndex.insert(std::pair<unsigned int, Edge2D*>(mEdges[mEdges.size() - 1].getID(), &mEdges[mEdges.size() - 1]));
	}

	assert(JsonDocument.HasMember("nodes"));
	assert(JsonDocument["nodes"].IsArray());
	const Value& NodeArray = JsonDocument["nodes"];
	for (SizeType i = 0; i < NodeArray.Size(); ++i) {
		assert(NodeArray[i].IsObject());

		auto& JsonNode = NodeArray[i];

		assert(JsonNode.HasMember("id"));
		assert(JsonNode["id"].IsUint());

		assert(JsonNode.HasMember("in"));
		assert(JsonNode["in"].IsArray());

		assert(JsonNode.HasMember("out"));
		assert(JsonNode["out"].IsArray());

		std::vector<unsigned int> InIDs;
		const Value& InArray = JsonNode["in"];
		for (SizeType j = 0; j < InArray.Size(); ++j) {
			assert(InArray[j].IsUint());
			InIDs.push_back(InArray[j].GetUint());
		}

		std::vector<unsigned int> OutIDs;
		const Value& OutArray = JsonNode["out"];
		for (SizeType j = 0; j < OutArray.Size(); ++j) {
			assert(OutArray[j].IsUint());
			OutIDs.push_back(OutArray[j].GetUint());
		}

		mNodes.push_back(visual::SFMLNode(JsonNode["id"].GetUint(), InIDs, OutIDs));
		mNodeIndex.insert(std::pair<unsigned int, Node2D*>(mNodes[mNodes.size() - 1].getID(), &mNodes[mNodes.size() - 1]));
	}

	for (auto& Edge : mEdges) {
		Edge.InitPointers(*this);
	}
	for (auto& Node : mNodes) {
		Node.InitPointers(*this);
	}
}

Environment::~Environment() {
	mVertexIndex.clear();
	mVertices.clear();

	mEdgeIndex.clear();
	mEdges.clear();

	mNodeIndex.clear();
	mNodes.clear();
}

const std::string& Environment::getName() const {
	return mName;
}

double Environment::getVersion() const {
	return mVersion;
}

Vertex2D* Environment::getVertex(unsigned int ID) const {
	assert(mVertexIndex.find(ID) != mVertexIndex.end());
	return mVertexIndex.at(ID);
}

const std::vector<Vertex2D*> Environment::getVertices(const std::vector<unsigned int>& IDs) const {
	vector<Vertex2D*> Result(IDs.size());

	for (size_t i = 0; i < IDs.size(); ++i) {
		Result[i] = getVertex(IDs[i]);
	}

	return Result;
}

std::vector<Vertex2D*> Environment::getAllVertices() const {
	std::vector<Vertex2D*> Result(mVertices.size());

	for (size_t i = 0; i < mVertices.size(); ++i) {
		Result[i] = &mVertices[i];
	}

	return Result;
}

Edge2D* Environment::getEdge(unsigned int ID) const {
	assert(mEdgeIndex.find(ID) != mEdgeIndex.end());
	return mEdgeIndex.at(ID);
}

const std::vector<Edge2D*> Environment::getEdges(const std::vector<unsigned int>& IDs) const {
	vector<Edge2D*> Result(IDs.size());

	for (size_t i = 0; i < IDs.size(); ++i) {
		Result[i] = getEdge(IDs[i]);
	}

	return Result;
}

const std::vector<Edge2D*> Environment::getAllEdges() const {
	return mEdges;
}

Node2D* Environment::getNode(unsigned int ID) const {
	assert(mNodeIndex.find(ID) != mNodeIndex.end());
	return mNodeIndex.at(ID);
}

const std::vector<Node2D*> Environment::getNodes(const std::vector<unsigned int>& IDs) const {
	vector<Node2D*> Result(IDs.size());

	for (size_t i = 0; i < IDs.size(); ++i) {
		Result[i] = getNode(IDs[i]);
	}

	return Result;
}

const std::vector<Node2D*> Environment::getAllNodes() const {
	return mNodes;
}