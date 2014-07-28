#pragma once
#include "afxwin.h"


// CAddWire dialog

class CAddWire : public CDialogEx
{
	DECLARE_DYNAMIC(CAddWire)

public:
	CAddWire(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddWire();

// Dialog Data
	enum { IDD = IDD_ADD_WIRE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_wire1;
	CEdit m_wire2;
	CString n1, n2;
	CString getStart(){return n1;};
	CString getEnd(){return n2;};
	void setStart(const CString& value) {n1 = value;}
	void setEnd(const CString& value) {n2 = value;}
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
