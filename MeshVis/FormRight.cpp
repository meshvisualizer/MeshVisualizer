// FormRight.cpp : implementation file
//

#include "stdafx.h"
#include "MeshVis.h"
#include "FormRight.h"
#include "Node.h"
#include "MeshVisDoc.h"

// CFormRight

IMPLEMENT_DYNCREATE(CFormRight, CFormView)

CFormRight::CFormRight()
	: CFormView(CFormRight::IDD)
{
}

CFormRight::~CFormRight()
{
}

void CFormRight::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormRight, CFormView)
	//ON_BN_CLICKED(IDC_BUTTON1, &CFormRight::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CFormRight::OnBnClickedOk)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//ON_BN_CLICKED(IDC_BUTTON1_HELLO, &CFormRight::OnBnClickedButton1Hello)
	//ON_BN_CLICKED(IDC_BUTTON1_HELLO, &CFormRight::OnBnClickedButton1Hello)
	ON_WM_MOUSEWHEEL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_XPlus, &CFormRight::OnBnClickedXplus)
	ON_BN_CLICKED(IDC_XMinus, &CFormRight::OnBnClickedXminus)
	ON_BN_CLICKED(IDC_YPlus, &CFormRight::OnBnClickedYplus)
	ON_BN_CLICKED(IDC_YMinus, &CFormRight::OnBnClickedYminus)
	ON_BN_CLICKED(IDC_ZPlus, &CFormRight::OnBnClickedZplus)
	ON_BN_CLICKED(IDC_ZMinus, &CFormRight::OnBnClickedZminus)
END_MESSAGE_MAP()


// CFormRight diagnostics

#ifdef _DEBUG
void CFormRight::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormRight::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormRight message handlers

void CFormRight::OnBnClickedOk()
{
	InvalidateRect(NULL, FALSE);
}

void CFormRight::RenderScene()
{
	CMeshVisDoc *pDoc=(CMeshVisDoc *)GetDocument();
	
	
	m_OpenGL.Init( (GetDC())->m_hDC );
	// TODO: Add your control notification handler code here
		////////// CLEAR BUFFERS ////////////////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	////////// SET UP 3D VIEWPORT ///////////////
	m_OpenGL.Set_Viewport3D();
	
	gluLookAt(0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glRotatef(rotate_x,1,0,0);
	glRotatef(rotate_y,0,1,0);
	glRotatef(rotate_z,0,0,1);
	{
		if(pDoc->GV->showNodes())
		{
			glPointSize(2);
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
				for(int j = 0; j<pDoc->GV->getNumNode(); j++)
				{
					std::string node = pDoc->GV->getNode(j)->toString();
					Node * tn = pDoc->GV->getNode(j);
					int id = tn->getID();
					double x = tn->getX()*scale; 
					double y = tn->getY()*scale;
					double z = tn->getZ()*scale;
					glVertex3d(x,y,z);		//Scaled by 100 for testing
				}
			glEnd();
		}


	
		
		int e = pDoc->GV->getNumElements();
		for(int i = 0; i < e; i ++)
		{
			std::vector<int> elementI = *pDoc->GV->getElement(i);
			//OutputDebugString(_T("\n got the element.\n"));
			int nodes = elementI[2];
			//CString num; 
			//num.Format(_T("\nElement:%d has %d nodes:\n"), i, nodes);
			//OutputDebugString(num);
			switch (nodes)
			{
			case 2: 
				{
					//OutputDebugString(_T("\nElement of type 2 (Line)\n"));
					glColor3f(0.0, 1.0, 0.0);
					glBegin(GL_LINES);
					for(int k =0; k < nodes; k++)
					{
						int nodeID = elementI[k+2];
						Node * tn = pDoc->GV->getNode(nodeID);
						/*
						double x =tn->getX();
						double y = tn->getY();
						double z = tn->getZ();
						*/
						double x =tn->getX()*scale;
						double y = tn->getY()*scale;
						double z = tn->getZ()*scale;
						//CString elem;
						//elem.Format(_T("node:%d x:%f y: %f z:%f\n"),tn->getID(),x,y,z);
						//OutputDebugString((LPCTSTR)elem);
						glVertex3d(x,y,z);
					}
					glEnd();
					break;
				}
			case 4: 
				{
					//OutputDebugString(_T("\nElement of type 4 (quad)\n"));
					glColor3f(0.0, 1.0, 1.0);
					for(int k =0; k < nodes; k++)//This may need to be changed to counter clock wise initialization meaning 0,1,3,2 instead of 0,1,2,3,
					{
						glBegin(GL_QUADS);
						int nodeID = elementI[k+3];
						Node * tn = pDoc->GV->getNode(nodeID);
						double x =tn->getX()*scale;
						double y = tn->getY()*scale;
						double z = tn->getZ()*scale;
						glVertex3d(x,y,z);
						glEnd();
					}
				
					break;
			case 8:
				{
					OutputDebugString(_T("\nThis will be a first order cube."));
					 
					glColor3f(1.0, 1.0, 0.0);
					//Right side quad:0,1,3,2
					glBegin(GL_QUADS);
					std::vector<double> tempv = pDoc->GV->getNodeVec(i, 0, scale);
					//CString num;
					//num.Format(_T("\nX:%d Y:%d Z:%d"), tempv[0], tempv[1],tempv[2]);
					//OutputDebugString(num);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					//glVertex3d(tempv);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					//Back quad:1,5,7,3
					glBegin(GL_QUADS);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					//Bottom quad: 3,7,6,2
					glBegin(GL_QUADS);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					//Left side quad: 4,5,7,6
					glBegin(GL_QUADS);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					//Top quad: 1,5,4,0
					glBegin(GL_QUADS);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 0, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					//Front quad: 0,4,6,2
					glBegin(GL_QUADS);
					tempv = pDoc->GV->getNodeVec(i, 0, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					break;
				}
			case 9:
				{
					OutputDebugString(_T("\nThis will be a 2nd order plate."));

					glColor3f(0.0, 0.0, 1.0);
					//0,3,4,1
					glBegin(GL_QUADS);
					std::vector<double> tempv = pDoc->GV->getNodeVec(i, 0, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					//1,4,5,2
					glBegin(GL_QUADS);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					//4,7,8,5
					glBegin(GL_QUADS);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 8, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					//3,6,7,4
					glBegin(GL_QUADS);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					break;
				}
			default: 
				OutputDebugString(_T("\nThis element type is not implemented yet."));
				}
			}
		}
	}
	glPopMatrix();

	OutputDebugString(_T("\ndone creating elements.\n"));

	if(pDoc->GV->showAxes())
	{
		glPushMatrix();
		glTranslatef(-17.0,-17.0,0);
		glRotatef(rotate_x,1,0,0);
		glRotatef(rotate_y,0,1,0);
		glRotatef(rotate_z,0,0,1);
		{
			//Axes
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
				glVertex3d(0.0, 0.0, 0.0);
				glVertex3d(6.0, 0.0, 0.0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3d(4.5,-0.5, 0.0);
				glVertex3d(6.0, 0.0, 0.0);
				glVertex3d(4.5, 0.5, 0.0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3d(4.5, 0.0,-0.5);
				glVertex3d(6.0, 0.0, 0.0);
				glVertex3d(4.5, 0.0, 0.5);
			glEnd();
			// Draw CSI y in Green
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_LINES);
				glVertex3d(0.0, 0.0, 0.0);
				glVertex3d(0.0, 6.0, 0.0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3d(0.5, 4.5, 0.0);
				glVertex3d(0.0, 6.0, 0.0);
				glVertex3d(-0.5,4.5, 0.0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3d(0.0, 4.5,-0.5);
				glVertex3d(0.0, 6.0, 0.0);
				glVertex3d(0.0, 4.5, 0.5);
			glEnd();
			// Draw CSI z in Blue
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_LINES);
				glVertex3d(0.0, 0.0, 0.0);
				glVertex3d(0.0, 0.0, 6.0);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3d(0.5, 0.0, 4.5);
				glVertex3d(0.0, 0.0, 6.0);
				glVertex3d(-0.5,0.0, 4.5);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3d(0.0, 0.5, 4.5);
				glVertex3d(0.0, 0.0, 6.0);
				glVertex3d(0.0,-0.5, 4.5);
			glEnd();

			glTranslatef(-50.0,-50.0,0);
			
		}
		glPopMatrix();
	}
	////////// SET UP 2D VIEWPORT ///////////////
	m_OpenGL.Set_Viewport2D();

	////////// RENDER 2D SCENE //////////////////

	////////// FINISH RENDERING /////////////////
	m_OpenGL.Finish_Render();





	
	OutputDebugString(_T("\nThe visualization should rotate\n"));
}


void CFormRight::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_OpenGL.Set_Viewport_Size(cx,cy);

	
}


void CFormRight::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: Add your message handler code here
	m_OpenGL.UnInit();
}


BOOL CFormRight::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}




void CFormRight::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}


BOOL CFormRight::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	//zDelta is the movement of mouse wheel val, this number should be used to adjust the 
	//viewport

	//CString num;
	//num.Format(_T("\nzDelta:%d"),zDelta);
	//OutputDebugString(num);

	if(zDelta>0)
		scale*=1.2;
	else
		scale*=0.8;
	InvalidateRect(NULL, FALSE);

	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}


void CFormRight::OnPaint()
{
	static bool init = false;
	CPaintDC dc(this); // device context for painting
	
	if(!init)
	{
		rotate_x=rotate_y=rotate_z=0;
		scale = findOptimalScale();
		init = true;
	}
	
	RenderScene();

	
}

float CFormRight::findOptimalScale()
{
	return 1;
}


void CFormRight::OnBnClickedXplus()
{
	rotate_x+=10;
	if(rotate_x>=360) rotate_x=0;
	InvalidateRect(NULL, FALSE);
}


void CFormRight::OnBnClickedXminus()
{
	rotate_x-=10;
	if(rotate_x<=0) rotate_x=360;
	InvalidateRect(NULL, FALSE);
}


void CFormRight::OnBnClickedYplus()
{
	rotate_y+=10;
	if(rotate_y>=360) rotate_y=0;
	InvalidateRect(NULL, FALSE);
}


void CFormRight::OnBnClickedYminus()
{
	rotate_y-=10;
	if(rotate_y<=0) rotate_y=360;
	InvalidateRect(NULL, FALSE);
}


void CFormRight::OnBnClickedZplus()
{
	rotate_z+=10;
	if(rotate_z>=360) rotate_z=0;
	InvalidateRect(NULL, FALSE);
}


void CFormRight::OnBnClickedZminus()
{
	rotate_z-=10;
	if(rotate_z<=0) rotate_z=360;
	InvalidateRect(NULL, FALSE);
}
