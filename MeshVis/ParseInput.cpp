// ParseInput.cpp : implementation file
//

#include "stdafx.h"
#include "MeshVis.h"
#include "ParseInput.h"

// ParseInput

ParseInput::ParseInput(CString fin)
{
	//std::string SIE = "SIE";		//To Yoshi: Are these two vars useful?
	//std::string FEM = "FEMIN";		//- Ce

	filename = fin;

}

ParseInput::~ParseInput()
{
}

int ParseInput::lineReader(GlobalVars *gv) 
{ 
	//OutputDebugString(_T("\nLineReader called\n"));
    std::ifstream file(filename);//will become the file name //will need a try catch somewhere
    std::string line; 
    while (std::getline(file, line))
    {
		Lines.push_back(line);
    }
	file.close();//not sure if this is needed at this point or later
	if(Lines[1].find("FEMIN")!= std::string::npos)
	{
		//OutputDebugString(_T("\nFound FEMIN\n"));
		gv->setFileType("FEMIN");
	}
	else if(Lines[1].find("SIE")!= std::string::npos)
	{
		//OutputDebugString(_T("\nFound SIE\n"));
		gv->setFileType("SIE");
	}
	else
	{
		//Unsupported File type
		OutputDebugString(_T("\nError: File type not supported.\n(Requires FEMIN,SIE types)\n"));
		return -1;
	}
	//OutputDebugString(_T("\nLineReader method finished\n"));
	return 1;
}

int ParseInput::getNodes(GlobalVars *gv)
{
	//OutputDebugString(_T("\ngetNodes was called\n"));
	int startInd, endInd;
	double maxx,maxy,minx,miny, maxz;
	std::string ft = gv->getFileType();
	if(ft == "SIE")
	{
		//OutputDebugString(_T("\nSIE IF executed."));
		startInd = findIndex(NODE_START_STR_SIE);
		endInd = findIndex(NODE_END_STR_SIE);
	}
	else if(ft == "FEMIN")
	{
		//OutputDebugString(_T("\nFEM IF executed."));
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
	gv->setNumNodes(numNodes);
	//OutputDebugString(_T("\nnumNodes should now be set"));
	if(ft == "SIE")
			{
				int units = atoi(Lines[startInd-1].c_str());
				gv->setUnits(units);
			}
	for ( int i = startInd; i < endInd; i++)
	{
		//METHOD HERE TO DELIMITE LINE OF NODES
		std::string strToParse = Lines[i];
		//CString ival;
		//ival.Format(_T("i = %d\n"), i);
		//OutputDebugString(ival);//These lines are for debugging purposes, they print the current line number
		strToParse.insert(strToParse.length()," ");
		std::string id_s = nextToken(&strToParse);
		std::string x_s = nextToken(&strToParse);
		std::string y_s = nextToken(&strToParse);
		std::string z_s = nextToken(&strToParse);
		
		int id = atoi(id_s.c_str());
		double x = atof(x_s.c_str());
		double y = atof(y_s.c_str());
		double z = atof(z_s.c_str());
		Node* n = new Node(id,x,y,z);
		if(id ==1)//initialize with first node vals
		{
			maxx = x;
			maxy = y;
			minx = x;
			miny = y;
			maxz = z;
		}
		else
		{
			if(x > maxx)
				maxx = x;
			if(x < minx)
				minx = x;
			if(y > maxy)
				maxy = y;
			if(y < miny)
				miny = y;
			if(z > maxz)
				maxz = z;
		}
		//ival.Format(_T("id:%d x:%f y:%f z: %f\n"), id,x,y,z);
		//OutputDebugString(ival); //these lines are for debugging they print the id and xyz values above comments must also be turned on for these to work or ival must be redecalred
		gv->addNode(n);
	}
	//NEED TO CATCH ERROR EITHER WITH TRY CATCH OR manual error checking
	//Current code will allow an invalid file to be read see d:/InputTest.Txt
	gv->setMaxX(maxx);
	gv->setMaxY(maxy);
	gv->setMaxZ(maxz);
	gv->setMinX(minx);
	gv->setMinY(miny);

	return numNodes;
}

int ParseInput::getElements(GlobalVars *gv)
{
	int startInd, endInd;
	std::string ft = gv->getFileType();
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
	CString inER;
	inER.Format(_T("\nInside the element read numEl:%d sti:%d endi:%d\n"),numElements,endInd,startInd);
	OutputDebugString(inER);

	gv->setNumElements(numElements);
	int numNodes;
	int max = 0;//I think this is for counting max node associations
	//Actually need to read the elements here
	std::vector<std::vector<int>*> eList;
	int count = startInd;
	double type;
	double order;	
	for(int i = startInd; i <endInd; i++ )
	{
		std::string current = Lines[i];
		std::string buf; // Have a buffer string
		std::stringstream ss(current);
		std::vector<std::string> tokens;
		
		while (ss >> buf)
			tokens.push_back(buf);
		int id = stoi(tokens[0]);
		int len = tokens.size();
		std::vector<int>* temp2 = new std::vector<int>;
		type = stof(tokens[1]);
		order = stof(tokens[2]);
		int j;
		int lastN;
		if(ft == "SIE")
		{
			numNodes = (int) pow(order,type);
			j=3;
			lastN = 3;
				if (type == 3) {
					numNodes = (int) pow(order+1,type);}
		}
		else if(ft == "FEMIN")
		{
			numNodes = len - 2;
			j=2;
			lastN =2;
		}
		temp2->push_back(id);//push ID @0
		if(ft == "SIE")
		{
			temp2->push_back(stoi(tokens[2]));//push order if SIE @1
		}
		else if(ft == "FEMIN")
		{
			temp2->push_back(stoi(tokens[1]));//push order if FEM @1
		}
		temp2->push_back(numNodes);//Push nunmber of nodes @2

		for(j; j < numNodes+lastN; j++)
		{
			//std::cout<<j<<":"<<tokens[j]<<"\n";
			int temp = std::stoi(tokens[j]);
			temp2->push_back(temp);
		}
		
		eList.push_back(temp2);//Add element to eList
	}//end of reader for loop
	/*
	for(int i =0; i < eList.size();i++)
	{
		std::cout<<"loop counter:"<<i<<" Element id:"<<(eList[i][0])<<" order:"<<eList[i][1]<<" nodes:"<<eList[i][2]<<"\n";
		for(int j =3; j< eList[i].size(); j++)
		{
			std::cout<<eList[i][j]<<" ";
		}
		std::cout<<"\n";
	}*/
	gv->setElementList(eList);
	return 1;
}


int ParseInput::findIndex(std::string s)
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

std::string ParseInput::nextToken(std::string *ps)	//by Ce
{
	std::string result;

	//trim leading spaces and tabs
	while((*ps)[0]==' ' || (*ps)[0]=='\t')
	{
		ps->erase(0,1);
	}

	//find the first token in the rest part
	int i;
	for(i=0;i<(ps->length());i++)
	{
		if((*ps)[i]==' ' || (*ps)[i]=='\t')
			break;
	}
	result =  ps->substr(0,i);
	ps->erase(0,i);				
	return result;
}



// ParseInput member functions
