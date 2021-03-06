#pragma once
#include "afxcmn.h"


// CFormLeft form view

class CFormLeft : public CFormView
{
	DECLARE_DYNCREATE(CFormLeft)

protected:
	CFormLeft();           // protected constructor used by dynamic creation
	virtual ~CFormLeft();

public:
	enum { IDD = IDD_FORM_LEFT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedNodes(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnInitialUpdate();
	CListCtrl m_Nodes;
//	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1Hello();
	CString xin, yin,zin;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1Hello2();
protected:
	CWnd* m_target;
public:
	void SetTarget(CWnd* m_cwnd);
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

