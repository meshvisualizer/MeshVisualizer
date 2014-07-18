// Node.cpp : implementation file
//

#include "stdafx.h"
#include "MeshVis.h"
#include "Node.h"


// Node

Node::Node()
{
	this->x=0;
	this->y=0;
	this->z=0;
}
/*
 Node::Node( const Node& other ) :
     ID( other.ID), x( other.x ), y( other.y ), z( other.y )
  {}*/

Node::Node(int id, double x, double y, double z){
	this->ID = id;//The ID will be grabbed frmo the global vars class not userinput.
	this->x = x;
	this->y = y;
	this->z = z;
}

std::string Node::toString()
{
	//std::string temp = "ID: ";
	//temp += std::to_string((_ULonglong)(this->ID));
	std::ostringstream nodeString;
	nodeString <<"ID:"<<this->ID<<" X:"<< this->x <<" Y:"<<this->y<<" Z:"<<this->z;
	std::string node = nodeString.str();
	return node;
}

Node::~Node()
{
}


// Node member functions
