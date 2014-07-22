// GlobalVars.cpp : implementation file
//

#include "stdafx.h"
#include "MeshVis.h"
#include "GlobalVars.h"


// GlobalVars
// GlobalVars member functions

Node* GlobalVars::getNode(int n)
{
	return this->nodeList[n];
}
GlobalVars::GlobalVars()
{
	this->numNodes = 0;
	this->numElements = 0;
	this->created = false;
	this->viewAxes = true;
	this->viewNodes = true;
}

GlobalVars::~GlobalVars()//Will need ot delete the node and element lists.
{
	
}

void GlobalVars::setNumNodes(int n)
{
	this->numNodes = n;
}

void GlobalVars::setNumElements(int e)
{
	this->numElements = e;
}

void GlobalVars::setUnits(int u)
{
	this->units = u;
}

void GlobalVars::setMaxNodeAssociations(int a)
{
	this->maxNodeAssociations = a;
}

void GlobalVars::setFileType(std::string f)
{
	this->fileType = f;
}

void GlobalVars::addNode(Node* n)
{
	this->nodeList.push_back(n);
}

void GlobalVars::setElementList(std::vector<std::vector<int>*> el)
{
	this->elementList = el;
}

std::vector<int>* GlobalVars::getElement(int n)
{
	return this->elementList[n];
}

void GlobalVars::setCreated(bool val)
{
	this->created = val;
}

void GlobalVars::setViewAxes(bool val)
{
	this->viewAxes = val;
}

void GlobalVars::setViewNodes(bool val)
{
	this->viewNodes = val;
}

std::vector<double> GlobalVars::getNodeVec(int e, int n, float scale)
{
	//int* xval = this->(*(elementList[e]))[n];
	std::vector<int>* nodes = this->elementList[e];
	int nodeID = (*nodes)[n+3]-1;
	std::vector<double> nvec = std::vector<double>(3);

	nvec[0] = this->nodeList[nodeID]->getX()*scale;
	nvec[1] = this->nodeList[nodeID]->getY()*scale;
	nvec[2] = this->nodeList[nodeID]->getZ()*scale;
	return nvec;
}