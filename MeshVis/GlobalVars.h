#pragma once

// GlobalVars command target
#include "stdafx.h"
#include "Node.h"
#include <vector>


class GlobalVars : public CObject
{
private:
	int numNodes;
	int numElements;
	int units;
	int maxNodeAssociations;
	std::string fileType;
	//List of nodes
	std::vector<Node*> nodeList; //May want to change this to pointers to nodes.
	std::vector<std::vector<int>*> elementList;
	bool created;
	//List of elements
	//std::vector<Element> elementList; //Element class not yet implemented.
public:
	//Constructors
	GlobalVars();
	//Destructor
	virtual ~GlobalVars();
	//Getters:
	int getNumNode(){return numNodes;};
	int getNumElements(){return numElements;};
	int getUnits(){return units;};
	int getMaxNodeAssociations(){return maxNodeAssociations;};
	bool getCreated(){return created;};
	std::string getFileType(){return fileType;};
	//int getNodesInElement(int n);//not needed yet.
	//std::vector<Node> getNodeList();
	Node* getNode(int n);
	std::vector<int>* getElement(int n);

	//Setters
	void setNumNodes(int n);
	void setNumElements(int e);
	void setUnits(int u);
	void setMaxNodeAssociations(int a);
	void setFileType(std::string f);
	void setElementList(std::vector<std::vector<int>*> el);
	void setCreated(bool val);
	//Operators
	void addNode(Node* n);//not implemented yet.
	

};


