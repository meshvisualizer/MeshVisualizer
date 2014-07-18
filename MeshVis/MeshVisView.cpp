
// MeshVisView.cpp : implementation of the CMeshVisView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MeshVis.h"
#endif

#include "MeshVisDoc.h"
#include "MeshVisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMeshVisView

IMPLEMENT_DYNCREATE(CMeshVisView, CView)

BEGIN_MESSAGE_MAP(CMeshVisView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMeshVisView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMeshVisView construction/destruction

CMeshVisView::CMeshVisView()
{
	// TODO: add construction code here

}

CMeshVisView::~CMeshVisView()
{
}

BOOL CMeshVisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//added following 2 lines 
	cs.style |= ( WS_CLIPCHILDREN | 
    WS_CLIPSIBLINGS | CS_OWNDC ); 
	return CView::PreCreateWindow(cs);
}

// CMeshVisView drawing

void CMeshVisView::OnDraw(CDC* /*pDC*/)
{
	CMeshVisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMeshVisView printing


void CMeshVisView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMeshVisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMeshVisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMeshVisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMeshVisView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMeshVisView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMeshVisView diagnostics

#ifdef _DEBUG
void CMeshVisView::AssertValid() const
{
	CView::AssertValid();
}

void CMeshVisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMeshVisDoc* CMeshVisView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMeshVisDoc)));
	return (CMeshVisDoc*)m_pDocument;
}
#endif //_DEBUG


// CMeshVisView message handlers

