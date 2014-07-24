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
	this->fileType = "";
	this->numNodes = 0;
	this->numElements = 0;
	this->created = false;
	this->viewAxes = true;
	this->viewNodes = true;
	this->fileOpen = false;
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

void GlobalVars::setFileOpen(bool val)
{
	this->fileOpen = val;
}

void GlobalVars::setMaxX(double n)
{
	this->maxX = n;
}

void GlobalVars::setMinX(double n)
{
	this->minX = n;
}

void GlobalVars::setMaxY(double n)
{
	this->maxY = n;
}

void GlobalVars::setMaxZ(double n)
{
	this->maxZ = n;
}
void GlobalVars::setMinY(double n)
{
	this->minY = n;
}
void GlobalVars::setDoScaling(bool val)
{
	this->doScaling = val;
}