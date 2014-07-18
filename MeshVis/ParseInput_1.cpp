#include "stdafx.h"
#include "ParseInput_1.h"


std::vector<std::string> LineReader() 
{ 
    std::ifstream file("Read.txt");//will become the file name //will need a try catch somewhere
    std::string line; 
	std::vector<std::string> lines;
    while (std::getline(file, line))
    {
		lines.push_back(line);
    }
	file.close();//not sure if this is needed at this point or later
	if(lines[1].find("FEMIN")!= std::string::npos)
	{
		GV.setFileType("FEMIN");
	}
	else if(lines[1].find("SIE")!= std::string::npos)
	{
		GV.setFileType("SIE");
	}
	else
	{
		//Unsupported File type
		std::cout <<"Error: File type not supported.\n(Requires FEMIN,SIE types)";
	}
	return lines;
}

int getNodes()
{
	int startInd, endInd;
	std::string ft = GV.getFileType();
	if(ft == "SIE")
	{
		startInd = findIndex(NODE_START_STR_SIE);
		endInd = findIndex(NODE_END_STR_SIE);
	}
	else if(ft == "FEMIN")
	{
		startInd = findIndex(NODE_START_STR_FEMIN);
		endInd = findIndex(NODE_END_STR_FEMIN);
	}
	for (int index = startInd; index < endInd; index++)//loop that reads the nodes
	{
		if(Lines[index].find("=====================================================data:")!= std::string::npos)
		{
			if(ft == "SIE")
			{
				startInd = index + 2;
			}
			else
			{
				startInd = index + 1;
			}
		}
		if(Lines[index].find("*************************")!= std::string::npos)
		{
			endInd = index;
			break;
		}
	}
	if (startInd > endInd) { return -1; }
	if (startInd == endInd) 
	{
		std::cout <<"Error: No nodes found.";
		return -1;
	}

	int numNodes = endInd - startInd;
	GV.setNumNodes(numNodes);

	if(ft == "SIE")
			{
				int units = atoi(Lines[startInd-1].c_str());
				GV.setUnits(units);
			}
	
	for ( int i = startInd; i < endInd; i++)
	{
		//METHOD HERE TO DELIMITE LINE OF NODES
		std::string strToParse = Lines[i];
		strToParse.insert(strToParse.length()," ");
		std::string id_s = nextToken(&strToParse);
		std::string x_s = nextToken(&strToParse);
		std::string y_s = nextToken(&strToParse);
		std::string z_s = nextToken(&strToParse);
		
		int id = atoi(id_s.c_str());
		double x = atof(x_s.c_str());
		double y = atof(y_s.c_str());
		double z = atof(z_s.c_str());
		Node n = Node(id,z,y,z);
		
		//GV.addNode(n);
	}
	return 1;
}
/*
int getElements()
{
	int startInd, endInd;
	std::string ft = GV.getFileType();
	if(ft == "SIE")
	{
		startInd = findIndex(ELEM_START_STR_SIE);
		endInd = findIndex(ELEM_END_STR_SIE);
	}
	else if(ft == "FEMIN")
	{
		startInd = findIndex(ELEM_START_STR_FEMIN);
		endInd = findIndex(ELEM_END_STR_FEMIN);
	}
	for (int index = startInd; index < endInd; index++)//loop that reads the nodes
	{
		if(Lines[index].find("=====================================================data:")!= std::string::npos)
		{
			startInd = index + 1;
		}
			if(Lines[index].find("*************************")!= std::string::npos)
		{
			endInd = index;
			break;
		}
	}
	int numElements = endInd - startInd;
	GV.setNumElements(numElements);
	int max = 0;//I think this is for counting max node associations
	//Actually need to read the elements here
}

*/
int findIndex(std::string s)
{
	for(int i = 0; i < Lines.size(); i++)
	{
		if(Lines[i]==s)
		{
			return i;
		}
	}
	return -1;
}

std::string nextToken(std::string *ps)	//by Ce
{
	std::string result;

	//trim leading spaces and tabs
	while((*ps)[0]==' ' || (*ps)[0]=='/t')
	{
		ps->erase(0,1);
	}

	//find the first token in the rest part
	int i;
	for(i=0;i<(ps->length());i++)
	{
		if((*ps)[i]==' ' || (*ps)[i]=='/t')
			break;
	}
	result =  ps->substr(0,i);
	ps->erase(0,i);				//remove the token has been just taken.
	return result;
}