// FormLeft.cpp : implementation file
//
#include "stdafx.h"
#include "MeshVis.h"
#include "FormLeft.h"
#include "Node.h"
#include "MeshVisDoc.h"
#include "AddNode.h"


// CFormLeft

IMPLEMENT_DYNCREATE(CFormLeft, CFormView)

CFormLeft::CFormLeft()
	: CFormView(CFormLeft::IDD)
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
					coord.Format(_T("%lf"), x);
					m_Nodes.SetItemText(i,j,coord);
					break;}
				case 2:{
					double y = n->getY();
					CString coord;
					coord.Format(_T("%lf"), y);
					m_Nodes.SetItemText(i,j,coord);
					break;}
				case 3: {
					double z = n->getZ();
					CString coord;
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
	if(addNode.DoModal()==IDOK)
	{
	xin = addNode.getX();
	yin = addNode.getY();
	zin = addNode.getZ();
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
	}
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
	}
