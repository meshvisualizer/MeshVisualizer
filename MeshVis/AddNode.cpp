// AddNode.cpp : implementation file
//

#include "stdafx.h"
#include "MeshVis.h"
#include "AddNode.h"
#include "FormLeft.h"
#include "afxdialogex.h"


// CAddNode dialog

IMPLEMENT_DYNAMIC(CAddNode, CDialogEx)

CAddNode::CAddNode(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddNode::IDD, pParent)
{

}

CAddNode::~CAddNode()
{
	//UpdateData(TRUE);
}

void CAddNode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_xNew);
	DDX_Control(pDX, IDC_EDIT2, m_yNew);
	DDX_Control(pDX, IDC_EDIT3, m_zNew);
}


BEGIN_MESSAGE_MAP(CAddNode, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddNode::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddNode message handlers


void CAddNode::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CFormLeft *pFl=(CFormLeft *)AfxGetMainWnd();
	//Fl->xin
	//CString xin,yin,zin;
	//m_xNew.GetWindowText(pFl->xin);
	//OutputDebugString(xin);
	//OutputDebugString(_T("\n"));
	//m_yNew.GetWindowText(pFl->yin);
	//OutputDebugString(yin);
	//OutputDebugString(_T("\n"));
	//m_zNew.GetWindowText(pFl->zin);
	//OutputDebugString(zin);
	//OutputDebugString(_T("\n"));
	GetDlgItemText(IDC_EDIT1, dx);
	GetDlgItemText(IDC_EDIT2, dy);
	GetDlgItemText(IDC_EDIT3, dz);
	CDialogEx::OnOK();
}




BOOL CAddNode::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	dx.Format(_T("%d"), 0);
	dy.Format(_T("%d"), 0);
	dz.Format(_T("%d"), 0);
	// TODO:  Add extra initialization here
	SetDlgItemText(IDC_EDIT1, dx);
	SetDlgItemText(IDC_EDIT2, dy);
	SetDlgItemText(IDC_EDIT3, dz);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
