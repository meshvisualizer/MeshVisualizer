
// MeshVisDoc.h : interface of the CMeshVisDoc class
//

#include "GlobalVars.h"
#include "Node.h"

#pragma once

//#include "ParseInput.h"

class CMeshVisDoc : public CDocument
{
protected: // create from serialization only
	CMeshVisDoc();
	DECLARE_DYNCREATE(CMeshVisDoc)

// Attributes
public:
	
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMeshVisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
	GlobalVars *GV;
};
