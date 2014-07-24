#pragma once
#include "afxwin.h"


// CAddNode dialog

class CAddNode : public CDialogEx
{
	DECLARE_DYNAMIC(CAddNode)

public:
	CAddNode(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddNode();

// Dialog Data
	enum { IDD = IDD_ADD_NODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_xNew;
	CEdit m_yNew;
	CEdit m_zNew;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString getX(){return dx;};
	CString getY(){return dy;};
	CString getZ(){return dz;};
	void setX(const CString& value) {dx = value;}
	void setY(const CString& value) {dy = value;}
	void setZ(const CString& value) {dz = value;}
	CString dx,dy,dz;
};
