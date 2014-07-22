
// MeshVisDoc.cpp : implementation of the CMeshVisDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MeshVis.h"
#endif

#include "MeshVisDoc.h"
#include "ParseInput.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMeshVisDoc

IMPLEMENT_DYNCREATE(CMeshVisDoc, CDocument)

BEGIN_MESSAGE_MAP(CMeshVisDoc, CDocument)
END_MESSAGE_MAP()


// CMeshVisDoc construction/destruction

CMeshVisDoc::CMeshVisDoc()
{
	// TODO: add one-time construction code here
	GV = new GlobalVars();
}

CMeshVisDoc::~CMeshVisDoc()
{
}

BOOL CMeshVisDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMeshVisDoc serialization

void CMeshVisDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
		//ar.m_strFileName;
		//GV = new GlobalVars();
		
		OutputDebugString(_T("\nName of file: "));
		OutputDebugString((LPCTSTR)ar.m_strFileName);
		OutputDebugString(_T("\n"));
		ParseInput *fin = &ParseInput(ar.m_strFileName);
		fin->lineReader(GV);
		CString numNodes; 
		CString temp;
		fin->getNodes(GV);
		fin->getElements(GV);
		//numNodes.Format(_T("\nNodes Number:%d\n"), fin->getNodes(GV));
		//OutputDebugString((LPCTSTR)numNodes);
		//temp.Format(_T("After file read:\nNumNodes in GV:%d\n"),GV->getNumNode());
		//OutputDebugString((LPCTSTR)temp);
		//OutputDebugString(_T("The nodes should now be stored into the GV node list\n"));
		
		//The next 2 for loops print out nodes and elements from the GV pointer for testing purposes.
		/*
		for(int j = 0; j<GV->getNumNode(); j++)
		{
			std::string node = GV->getNode(j)->toString();
			Node * tn = GV->getNode(j);
			int id = tn->getID();
			double x = tn->getX(); 
			double y = tn->getY();
			double z = tn->getZ();
			CString Cnode;
			Cnode.Format(_T("loop val: %d\n id: %d x:%f y:%f z:%f\n"), j, id,x,y,z);
			OutputDebugString((LPCTSTR)Cnode);
		}
		for(int k = 0; k < GV->getNumElements(); k++)
		{
			std::vector<int>* temp = GV->getElement(k);
			int len = temp->size();
			CString elem;
			elem.Format(_T("Element: %d Order:%d Has %d nodes:\n"),(*temp)[0], (*temp)[1], (*temp)[2]);
			OutputDebugString((LPCTSTR)elem);
			for(int inner = 3; inner < len; inner++)
			{
				int val = (*temp)[inner];
				CString node;
				node.Format(_T("%d "),val);
				OutputDebugString((LPCTSTR)node);
				
			}
			OutputDebugString(_T("\n"));
		}*/  //END OF PRINTING
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMeshVisDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMeshVisDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMeshVisDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMeshVisDoc diagnostics

#ifdef _DEBUG
void CMeshVisDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMeshVisDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMeshVisDoc commands


void CMeshVisDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetTitle(_T("Electromagnetics Mesh Visualizer"));
}
