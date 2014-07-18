// FormRight.cpp : implementation file
//

#include "stdafx.h"
#include "MeshVis.h"
#include "FormRight.h"


// CFormRight

IMPLEMENT_DYNCREATE(CFormRight, CFormView)

CFormRight::CFormRight()
	: CFormView(CFormRight::IDD)
{

}

CFormRight::~CFormRight()
{
}

void CFormRight::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormRight, CFormView)
	//ON_BN_CLICKED(IDC_BUTTON1, &CFormRight::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CFormRight::OnBnClickedOk)
END_MESSAGE_MAP()


// CFormRight diagnostics

#ifdef _DEBUG
void CFormRight::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormRight::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormRight message handlers


void CFormRight::OnBnClickedOk()
{
	exit(0);
	// TODO: Add your control notification handler code here
}

void CFormRight::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}
