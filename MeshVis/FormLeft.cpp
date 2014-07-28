// FormLeft.cpp : implementation file
//
#include "stdafx.h"
#include "MeshVis.h"
#include "FormLeft.h"
#include "Node.h"
#include "MeshVisDoc.h"
#include "AddNode.h"
#include "AddWire.h"
#include "FormRight.h"
#include <cctype>
#include <cmath>

bool isNum(CString s)
{

	int i = 0;
	OutputDebugString(_T("\n"));
	CString temp = _T("-");
	CString temp1 = _T(".");
	if(s[i] == temp)
		i++;
	for(i; i<s.GetLength(); i++) 
	{
			if(!std::isdigit(s[i]))
				if(s[i]!=temp1)
					return false;

			
	}
	return true;
}
// CFormLeft

IMPLEMENT_DYNCREATE(CFormLeft, CFormView)

CFormLeft::CFormLeft()
	: CFormView(CFormLeft::IDD)
	, m_target(NULL)
{
	//DWORD SetExtendedStyle(LVS_EX_GRIDLINES);
	//m_Nodes.InsertColumn(0, _T("Node ID"), 0,-1,-1);
	//m_Nodes.InsertItem(0, _T("firsttest"));
	//
	//m_Nodes.InsertColumn(0, _T("Node ID:"));
	xin = "0";
	yin = "0";
	zin = "0";
	
}

CFormLeft::~CFormLeft()
{
}

void CFormLeft::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_NODES, m_Nodes);
	DDX_Control(pDX, IDC_LIST2, m_Nodes);
}

BEGIN_MESSAGE_MAP(CFormLeft, CFormView)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CFormLeft::OnLvnItemchangedList1)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CFormLeft::OnLvnItemchangedList2)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CFormLeft::OnItemchangedList2)
ON_BN_CLICKED(IDC_BUTTON1_HELLO, &CFormLeft::OnBnClickedButton1Hello)
ON_BN_CLICKED(IDC_BUTTON2, &CFormLeft::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON1_HELLO2, &CFormLeft::OnBnClickedButton1Hello2)
END_MESSAGE_MAP()


// CFormLeft diagnostics

#ifdef _DEBUG
void CFormLeft::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormLeft::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormLeft message handlers


void CFormLeft::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CFormLeft::OnLvnItemchangedNodes(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}



void CFormLeft::OnInitialUpdate()
{
	//OutputDebugString(_T("\nThe on Initial Update method was called.\n"));
	
	CFormView::OnInitialUpdate();
	CMeshVisDoc *pDoc=(CMeshVisDoc *)GetDocument();
	if(!pDoc->GV->getCreated())
	{
		int a,b,c,d;
		m_Nodes.SetExtendedStyle(LVS_EX_GRIDLINES);
		a = m_Nodes.InsertColumn(0,_T("Node ID"),0,55,-1);
		b = m_Nodes.InsertColumn(1,_T("X"),0,70,-1);
		c = m_Nodes.InsertColumn(2,_T("Y"),0,70,-1);
		d = m_Nodes.InsertColumn(3,_T("Z"),0,70,-1);
		/*m_Nodes.SetColumnWidth(0, 55);
		m_Nodes.SetColumnWidth(1, 70);
		m_Nodes.SetColumnWidth(2, 70);
		m_Nodes.SetColumnWidth(3, 70);*/
		pDoc->GV->setCreated(true);
	}
	//CString testing;
	//testing.Format(_T("THIS ONE: %d"), pDoc->GV->getNumNode());
//	OutputDebugString(testing);
	/******************************************************************************************************/
	for(int i = 0; i < pDoc->GV->getNumNode(); i++)//Loop for nodes 
		{
			Node* n = pDoc->GV->getNode(i);

			int id = n->getID();
			TCHAR buf[32];
			LPCTSTR ID = _itot(id, buf, 10);//Type needed to print to list.
			m_Nodes.InsertItem(i,(LPCTSTR)ID);//INSERT THE NODE ID
			for(int j = 1; j <= 3; j++)
			{
			//double    coord = 3.141*i*j; //Double coordiante value
				switch (j)
				{
				case 1:{
					double x = n->getX();
					CString coord;
					if(std::abs(x) < 0.00009)
						coord.Format(_T("%.9f"),x);
					else
						coord.Format(_T("%lf"), x);
					m_Nodes.SetItemText(i,j,coord);
					break;}
				case 2:{
					double y = n->getY();
					CString coord;
					if(std::abs(y) < 0.00009)
						coord.Format(_T("%.9f"),y);
					else
						coord.Format(_T("%lf"), y);
					m_Nodes.SetItemText(i,j,coord);
					break;}
				case 3: {
					double z = n->getZ();
					CString coord;
					if(std::abs(z) < 0.00009)
						coord.Format(_T("%.9f"),z);
					else
						coord.Format(_T("%lf"), z);
					m_Nodes.SetItemText(i,j,coord);
					break;}
				}
			}

	/*******************************************************************************************************/
	//for(int i = 0; i < 100; i++)//Loop for nodes 
	//{
	//	
	//	int value = i+1;
	//	TCHAR buf[32];
	//	LPCTSTR ID = _itot(value, buf, 10);//Type needed to print to list.
	//	//m_Nodes.InsertItem(i,(LPCTSTR)ID);//INSERT THE NODE ID
	//	for(int j = 1; j <= 3; j++)
	//	{
	//		double    coord = 3.141*i*j; //Double coordiante value
	//		CString Scoord; 
	//		Scoord.Format(_T("%f"), coord);
	//		//m_Nodes.SetItemText(i,j,Scoord);//INSERT OF THE COORDINATE
	//	}

		//This line ends the area
	//m_Nodes.InsertItem(0,_T("E1-1"));
	//m_Nodes.SetItemText(0,1,strBuffer);
	//m_Nodes.SetItemText(0,2,_T("Y1"));
	//m_Nodes.SetItemText(0,3,_T("Z1"));
	//m_Nodes.InsertItem(
	//m_Nodes.InsertItem(1,_T("E1-2"));
	//}
	//m_Nodes.SetItemText(0,1,_T("Text1"));
	//m_Nodes.InsertColumn(ColNum, -T("ColLabel"),Format, width(in pixel), subitem)
	//OutputDebugString("Debug line print\n");
	// TODO: Add your specialized code here and/or call the base class
}

}


//void CFormLeft::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}


void CFormLeft::OnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	OutputDebugString(_T("A change was attempted.\n"));
	*pResult = 0;
}



/*
BOOL CFormLeft::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	return CFormView::OnCommand(wParam, lParam);
}
*/

	void CFormLeft::OnBnClickedButton1Hello()
{
	// TODO: Add your control notification handler code here
	CString xin,yin,zin, vals;
	CAddNode addNode;
	bool attempt = true;
	while(attempt)
	{
	if(addNode.DoModal()==IDOK)
	{
	xin = addNode.getX();
	yin = addNode.getY();
	zin = addNode.getZ();
	if(!isNum(xin))
	{
		MessageBox(_T("Error Invalid Coordinate:\nX value was not a number."), _T("Error"), MB_ICONERROR | MB_OK);
	}
	else if(!isNum(yin))
	{
		MessageBox(_T("Error Invalid Coordinate:\nY value was not a number."), _T("Error"), MB_ICONERROR | MB_OK);
	}
	else if(!isNum(zin))
	{
		MessageBox(_T("Error Invalid Coordinate:\nZ value was not a number."), _T("Error"), MB_ICONERROR | MB_OK);
	}
	else
	{
	//vals.Format(_T("\nx:%s y:%s z:%s\n"), xin, yin,zin);
	//OutputDebugString(vals);
	double xNew = _tstof(xin);
	double yNew = _tstof(yin);
	double zNew = _tstof(zin);
	//vals.Format(_T("\nx:%f y:%f z:%f\n"), xNew, yNew,zNew);
	//OutputDebugString(vals);
	CMeshVisDoc *pDoc=(CMeshVisDoc *)GetDocument();
	int currentID = pDoc->GV->getNumNode();
	//vals.Format(_T("currentID:%d\n"), currentID);
	//OutputDebugString(vals);
	int nextID = currentID+1;
	//vals.Format(_T("nextID:%d\n"), nextID);
	//OutputDebugString(vals);
	Node * n = new Node(nextID, xNew,yNew,zNew);
	pDoc->GV->addNode(n);
	pDoc->GV->setNumNodes(nextID);
	if(currentID == 0)//If this is first node
	{
		pDoc->GV->setMaxX(xNew);
		pDoc->GV->setMaxY(yNew);
		pDoc->GV->setMaxZ(zNew);
		pDoc->GV->setMinX(xNew);
		pDoc->GV->setMinY(yNew);
	}
	else
	{
		if(xNew > pDoc->GV->getMaxX())
		{
			pDoc->GV->setMaxX(xNew);
		}
		if(yNew > pDoc->GV->getMaxY())
		{
			pDoc->GV->setMaxY(yNew);
		}
		if(zNew > pDoc->GV->getMaxZ())
		{
			pDoc->GV->setMaxZ(zNew);
		}
		if(xNew < pDoc->GV->getMinX())
		{
			pDoc->GV->setMinX(xNew);
		}
		if(yNew < pDoc->GV->getMinY())
		{
			pDoc->GV->setMinY(yNew);
		}
	}
	TCHAR buf[32];
	LPCTSTR IDN = _itot(nextID, buf, 10);
	m_Nodes.InsertItem(nextID,(LPCTSTR)IDN);
	//m_Nodes.SetItemText(nextID,0,xin);
	m_Nodes.SetItemText(nextID-1,1,xin);
	m_Nodes.SetItemText(nextID-1,2,yin);
	m_Nodes.SetItemText(nextID-1,3,zin);
	pDoc->GV->setDoScaling(true);
	//pDoc->GV->setFileOpen(true);
	//pDoc->GV->setCreated(true);
	//pDoc->GV->setViewAxes(false);
	attempt = false;
	//CFormRight *pDoc1=(CFormRight *)GetDocument();
	//pDoc1->refresh();
	//CFormView::InvalidateRect(NULL, FALSE);
	//CView 
	//CView::InvalidateRect(NULL, FALSE);
	}//end of valid inputs
	}//end of if OK
	else
		attempt = false;
	}//end of while
}


	void CFormLeft::OnBnClickedButton2()
	{
		// TODO: Add your control notification handler code here
		CMeshVisDoc *pDoc=(CMeshVisDoc *)GetDocument();
		for(int j = 0; j<pDoc->GV->getNumNode(); j++)
		{
			//std::string node = pDoc->GV->getNode(j)->toString();
			Node * tn = pDoc->GV->getNode(j);
			int id = tn->getID();
			double x = tn->getX(); 
			double y = tn->getY();
			double z = tn->getZ();
			CString Cnode;
			Cnode.Format(_T("loop val: %d\n id: %d x:%f y:%f z:%f\n"), j, id,x,y,z);
			OutputDebugString((LPCTSTR)Cnode);
		}

		for(int k = 0; k < pDoc->GV->getNumElements(); k++)
		{
			std::vector<int>* temp = pDoc->GV->getElement(k);
			int len = temp->size();
			CString elem;
			elem.Format(_T("Element: %d Order:%d Has %d nodes:\n"),(*temp)[0], (*temp)[1], (*temp)[2]);
			OutputDebugString((LPCTSTR)elem);
			for(int inner = 3; inner < len; inner++)
			{
				int val = (*temp)[inner];
				CString node;
				node.Format(_T("%d "),val);
				OutputDebugString((LPCTSTR)node);
				
			}
			OutputDebugString(_T("\n"));
		}
	}


	void CFormLeft::OnBnClickedButton1Hello2()
	{
		// TODO: Add your control notification handler code here
		CString first,second, vals;
		CAddWire addWire;
		bool attempt = true;
		while(attempt)
		{
		if(addWire.DoModal()==IDOK)
		{
			first = addWire.getStart();
			second = addWire.getEnd();
			vals.Format(_T("\n1:%s n2:%s\n"), first, second);
			OutputDebugString(vals);
			int n1 = _tstoi(first);
			int n2 = _tstoi(second);
		
			CMeshVisDoc *pDoc=(CMeshVisDoc *)GetDocument();
			int currentID = pDoc->GV->getNumElements();
			int numNodes = pDoc->GV->getNumNode();
			if(numNodes == 0)
			{
				MessageBox(_T("There are no nodes in the project."), _T("Error"), MB_ICONERROR | MB_OK);
				attempt = false;
				//OutputDebugString(_T("\nThere are no nodes in the project.\n"));
				//return;
			}
			else if(numNodes < 2)
			{
				MessageBox(_T("Invalid Wire Element:There are not enough nodes in the project."), _T("Error"), MB_ICONERROR | MB_OK);
				attempt = false;
				//OutputDebugString(_T("\nInvalid Wire element:There are not enough nodes in the project.\n"));
				//return;
			}
			else if(n1 < 1)
			{
				MessageBox(_T("Invalid Node ID: Node IDs start from 1.\nOnly numbers are accepted."), _T("Error"), MB_ICONERROR | MB_OK);
				//OutputDebugString(_T("\nInvalid node ID was chosen.\n"));
				//return;
			}
			
			else if(n1 > numNodes || n2 > numNodes)
			{
				MessageBox(_T("Invalid Wire Element: Node ID out of range."), _T("Error"), MB_ICONERROR | MB_OK);
				//OutputDebugString(_T("\nInvalid Wire element: Node ID out of range.\n"));
				//return;
			}
			else {
			int nextID = currentID +1;
			std::vector<int>* temp2 = new std::vector<int>;
			temp2->push_back(nextID);
			temp2->push_back(1);
			temp2->push_back(2);
			temp2->push_back(n1);
			temp2->push_back(n2);
			pDoc->GV->addElement(temp2);
			attempt = false;
			}
		}
		else
			attempt = false;
		}

	}


	void CFormLeft::SetTarget(CWnd* m_cwnd)
	{
		m_target = m_cwnd;
	}


//	BOOL CFormLeft::OnCommand(WPARAM wParam, LPARAM lParam)
//	{
//		// TODO: Add your specialized code here and/or call the base class
//		if(m_target)
//		{           
//			m_target->SendMessage(WM_COMMAND, wParam, lParam);
//		}
//		else
//		{
//			CFormView::OnCommand(wParam, lParam);
//		}
//		return true;
//		//return CFormView::OnCommand(wParam, lParam);//This was the original line of code
//	}
