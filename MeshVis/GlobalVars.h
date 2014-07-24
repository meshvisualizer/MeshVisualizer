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
	double maxX; //planning to use these for dynamic sizing
	double minX;
	double maxY;
	double minY;
	double maxZ;
	std::string fileType;
	//List of nodes
	std::vector<Node*> nodeList; //May want to change this to pointers to nodes.
	std::vector<std::vector<int>*> elementList;
	bool created;
	bool fileOpen;
	bool viewNodes;
	bool viewAxes;
	bool doScaling;
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
	bool showNodes(){return viewNodes;};
	bool getDoScaling(){return doScaling;};
	bool showAxes(){return viewAxes;};
	bool getFileOpen(){return fileOpen;};
	Node* getNode(int n);
	std::vector<int>* getElement(int n);
	std::vector<double> getNodeVec(int e, int n, float scale);
	double getMaxX(){return maxX;};
	double getMinX(){return minX;};
	double getMaxY(){return maxY;};
	double getMinY(){return minY;};
	double getMaxZ(){return maxZ;};

	//int getNodesInElement(int n);//not needed yet.
	//std::vector<Node> getNodeList();

	//Setters
	void setFileOpen(bool val);
	void setNumNodes(int n);
	void setNumElements(int e);
	void setUnits(int u);
	void setMaxNodeAssociations(int a);
	void setFileType(std::string f);
	void setElementList(std::vector<std::vector<int>*> el);
	void setCreated(bool val);
	void setViewNodes(bool val);
	void setViewAxes(bool val);
	void setMaxX(double n);
	void setMinX(double n);
	void setMaxY(double n);
	void setMinY(double n);
	void setMaxZ(double n);
	void setDoScaling(bool val);

	//Operators
	void addNode(Node* n);//not implemented yet.
	

};


