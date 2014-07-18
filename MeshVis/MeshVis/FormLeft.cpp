// FormLeft.cpp : implementation file
//
#include "stdafx.h"
#include "MeshVis.h"
#include "FormLeft.h"



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
	CFormView::OnInitialUpdate();
	int a,b,c,d;
	m_Nodes.SetExtendedStyle(LVS_EX_GRIDLINES);

	
	a = m_Nodes.InsertColumn(0,_T("Node ID"),0,55,-1);
	b = m_Nodes.InsertColumn(1,_T("X"),0,50,-1);
	c = m_Nodes.InsertColumn(2,_T("Y"),0,50,-1);
	d = m_Nodes.InsertColumn(3,_T("Z"),0,50,-1);
	//m_Nodes.InsertItem(
	//m_Nodes.InsertColumn(ColNum, -T("ColLabel"),Format, width(in pixel), subitem)
	//OutputDebugString("Debug line print\n");
	// TODO: Add your specialized code here and/or call the base class
}


