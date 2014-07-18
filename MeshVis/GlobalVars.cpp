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