#pragma once
#include "Node.h"
#include "GlobalVars.h"
#include <fstream>
#include <sstream>
#include <vector>

#define NODE_START_STR_SIE  "   5. COORDINATES OF NODES (NNOD+1 lines):"
#define NODE_START_STR_FEMIN "   3. GLOBAL NODES DESCRIPTION (Node lines):"
#define NODE_END_STR_SIE "   6. DESCRIPTION OF ELEMENTS (NEL lines):"
#define NODE_END_STR_FEMIN "   4. 3D ELEMENT NODES DESCRIPTION (Element lines):"
#define ELEM_START_STR_SIE "   6. DESCRIPTION OF ELEMENTS (NEL lines):"
#define ELEM_START_STR_FEMIN "   4. 3D ELEMENT NODES DESCRIPTION (Element lines):"
#define ELEM_END_STR_SIE "   7. DEFINITION OF WIRE-SURFACE JUNCTIONS (NWSJUN lines):"
#define ELEM_END_STR_FEMIN "   5. 2D ELEMENT NODES DESCRIPTION (Element lines):"


class ParseInput : public CObject
{
private:
	//GlobalVars GV;//This object will need to be put at a higher level then passed down. Leaving here so file io can be implemented.
	CString filename;
	std::string SIE;
	std::string FEM;
	std::vector<std::string> Lines; //Place to store lines from file
	int findIndex(std::string s);
	std::string nextToken(std::string *ps);	//Find next token in a string.by Ce
public:
	ParseInput(CString filename);
	virtual ~ParseInput();
	int getNodes(GlobalVars *gv);
	int getElements(GlobalVars *gv);
	void lineReader(GlobalVars *gv);//Method for reading lines

};


