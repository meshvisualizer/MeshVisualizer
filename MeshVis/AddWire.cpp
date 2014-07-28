// AddWire.cpp : implementation file
//

#include "stdafx.h"
#include "MeshVis.h"
#include "AddWire.h"
#include "FormLeft.h"
#include "afxdialogex.h"


// CAddWire dialog

IMPLEMENT_DYNAMIC(CAddWire, CDialogEx)

CAddWire::CAddWire(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddWire::IDD, pParent)
{

}

CAddWire::~CAddWire()
{
}

void CAddWire::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT5, m_wire1);
	DDX_Control(pDX, IDC_EDIT4, m_wire2);
}


BEGIN_MESSAGE_MAP(CAddWire, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddWire::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddWire message handlers


void CAddWire::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT5, n1);
	GetDlgItemText(IDC_EDIT4, n2);
	CDialogEx::OnOK();
}


BOOL CAddWire::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	n1.Format(_T("%d"), 1);
	n2.Format(_T("%d"), 2);
	SetDlgItemText(IDC_EDIT5, n1);
	SetDlgItemText(IDC_EDIT4, n2);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
