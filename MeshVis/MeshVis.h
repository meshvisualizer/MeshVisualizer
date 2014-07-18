
// MeshVis.h : main header file for the MeshVis application
//
//#include "GlobalVars.h"
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMeshVisApp:
// See MeshVis.cpp for the implementation of this class
//

class CMeshVisApp : public CWinAppEx
{
public:
	CMeshVisApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
//	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	virtual BOOL OnIdle(LONG lCount);
};

extern CMeshVisApp theApp;
