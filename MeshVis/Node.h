#pragma once

// Node command target

class Node : public CObject
{
private: 
	int ID;
	double x;
	double y;
	double z;

public:
	Node();//default constructor
	Node(int id, double	x, double y, double z);//Constructor
	//Node( const Node& other );
	//getters
	int getID() {return ID;};
	double getX() { return x; };
	double getY() { return y; };
	double getZ() { return z; };
	//double getDis( Node N ); //able to calculate the distance between itself and another node
	//void alterNode(double x, double y, double z);//to change coords of existing node;setter for all 3 coords
	std::string toString();
	virtual ~Node();//destructor
};


