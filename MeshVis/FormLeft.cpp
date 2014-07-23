// FormLeft.cpp : implementation file
//
#include "stdafx.h"
#include "MeshVis.h"
#include "FormLeft.h"
#include "Node.h"
#include "MeshVisDoc.h"


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