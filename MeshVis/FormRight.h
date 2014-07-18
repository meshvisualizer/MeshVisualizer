#include "OpenGL.h"	
#pragma once



// CFormRight form view

class CFormRight : public CFormView
{
	DECLARE_DYNCREATE(CFormRight)

protected:
	CFormRight();           // protected constructor used by dynamic creation
	virtual ~CFormRight();

public:
	enum { IDD = IDD_FORM_RIGHT };
	COpenGL m_OpenGL;
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnBnClickedButton1Hello();
	virtual void OnInitialUpdate();
};


