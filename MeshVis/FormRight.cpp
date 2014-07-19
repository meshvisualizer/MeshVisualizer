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
	ON_BN_CLICKED(IDC_BUTTON1_HELLO, &CFormRight::OnBnClickedButton1Hello)
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
	CMeshVisDoc *pDoc=(CMeshVisDoc *)GetDocument();
	
	static float rotation = 0;
	m_OpenGL.Init( (GetDC())->m_hDC );
	// TODO: Add your control notification handler code here
		////////// CLEAR BUFFERS ////////////////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	////////// SET UP 3D VIEWPORT ///////////////
	m_OpenGL.Set_Viewport3D();
	
	gluLookAt(0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


	glPushMatrix();
	{
		glRotatef(++rotation,0,1,0);
		{
			glPointSize(2);
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
				for(int j = 0; j<pDoc->GV->getNumNode(); j++)
				{
					std::string node = pDoc->GV->getNode(j)->toString();
					Node * tn = pDoc->GV->getNode(j);
					int id = tn->getID();
					double x = tn->getX(); 
					double y = tn->getY();
					double z = tn->getZ();
					glVertex3f(x*10,y*10,z*10);		//Scaled by 10 for testing
				}
			glEnd();
		}
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-10.0,-10.0,0);
		glRotatef(rotation,0,1,0);
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
	}
	glPopMatrix();

	////////// SET UP 2D VIEWPORT ///////////////
	m_OpenGL.Set_Viewport2D();

	////////// RENDER 2D SCENE //////////////////

	////////// FINISH RENDERING /////////////////
	m_OpenGL.Finish_Render();

	if (rotation >= 358)
		rotation = 0;
	else
		rotation+=2;
	
	OutputDebugString(_T("\nThe button was pressed however,\nThis should in no way alter the original program so \n it really better not\n"));
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



void CFormRight::OnBnClickedButton1Hello()
{
	// TODO: Add your control notification handler code here
	OutputDebugString(_T("\nYou hit the button\n"));
}


void CFormRight::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	float rotation = 0;
	m_OpenGL.Init( (GetDC())->m_hDC );
	// TODO: Add your control notification handler code here
		////////// CLEAR BUFFERS ////////////////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	////////// SET UP 3D VIEWPORT ///////////////
	m_OpenGL.Set_Viewport3D();
	
	gluLookAt(0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// draw two spinning triangles, back to back
	glPushMatrix();
	{
		glRotatef(rotation,0,1,0);
		{
			/*glBegin(GL_TRIANGLES);
			{
				// first triangle
				glColor3f(  0.0f,  1.0f, 0.0f);
				glVertex3f( 0.0f, 15.0f, 0.0f);

				glColor3f(    0.0f,   1.0f, 0.0f);
				glVertex3f( -15.0f, -15.0f, 0.0f);

				glColor3f(   0.0f,   0.0f, 0.0f);
				glVertex3f( 15.0f, -15.0f, 0.0f);

				// second triangle
				glColor3f(  0.0f,  0.0f, 1.0f);
				glVertex3f( 0.0f, 15.0f, 0.0f);

				glColor3f(  0.0f,   0.0f, 0.0f);
				glVertex3f(15.0f, -15.0f, 0.0f);

				glColor3f(    0.0f,   0.0f, 1.0f);
				glVertex3f( -15.0f, -15.0f, 0.0f);
			}
			glEnd();*/
			GLint NumberOfPoints = 10;
			GLfloat x[10],y[10], z[10];
			for(int i = 0; i < 10; i++){
			x[i] = y[i] = z[i] = (GLfloat) i;
			}
			glPointSize(5);
			glColor3f(1.0, 0.0, 0.0);
			//glBegin( GL_POINTS ); //Chaing this to GL_POINTS to only see the nodes.
			/*
			for ( int i = 0; i < NumberOfPoints; ++i )
			{
			glVertex3f( x[i], y[i], z[i]);
			}*/
			//glVertex3f( 0, 0, 0);
			/*float vertex3f[] = {
			0.0f,0.0f,0.0f,
			10.0f,0.0f,0.0f,
			10.0f,10.0f,0.0f,
			0.0f,10.0f,0.0f,
			0.0f,0.0f,10.0f,
			10.0f,0.0f,10.0f,
			10.0f,10.0f,10.0f,
			0.0f,10.0f,10.0f
			};*/
			glBegin(GL_QUADS);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(10.0,0.0,0.0);
			glVertex3f(10.0,10.0,0.0);
			glVertex3f(0.0,10.0,0.0);
			glEnd();
			
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_QUADS);
			glVertex3f(0.0,0.0,-10.0);
			glVertex3f(10.0,0.0,-10.0);
			glVertex3f(10.0,10.0,-10.0);
			glVertex3f(0.0,10.0,-10.0);
		glEnd();
		//glBegin(GL_QUAD)
		glColor3f(0.0, 1.0, 0.0);
		glLineWidth(2.0);
		glBegin(GL_LINES);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(10.0,0.0,0.0);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(10.0,0.0,0.0);
			glVertex3f(10.0,10.0,0.0);
			glEnd();

		glBegin(GL_LINES);
			glVertex3f(10.0,10.0,0.0);
			glVertex3f(0.0,10.0,0.0);
			glEnd();

		glBegin(GL_LINES);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,10.0,0.0);
			glEnd();

			//glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_LINES);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,0.0,-10.0);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(10.0,0.0,0.0);
			glVertex3f(10.0,0.0,-10.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(10.0,10.0,0.0);
			glVertex3f(10.0,10.0,-10.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(0.0,10.0,0.0);
			glVertex3f(0.0,10.0,-10.0);
			glEnd();

			//glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex3f(0.0,0.0,-10.0);
			glVertex3f(10.0,0.0,-10.0);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(10.0,0.0,-10.0);
			glVertex3f(10.0,10.0,-10.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(10.0,10.0,-10.0);
			glVertex3f(0.0,10.0,-10.0);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(0.0,0.0,-10.0);
			glVertex3f(0.0,10.0,-10.0);
			glEnd();
			
			//Axes
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex3f(-10.0,0.0,0.0);
			glVertex3f(10.0,0.0,0.0);
			glEnd();
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_LINES);
			glVertex3f(0.0,-10.0,0.0);
			glVertex3f(0.0,10.0,0.0);
			glEnd();
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_LINES);
			glVertex3f(0.0,0.0,-10.0);
			glVertex3f(0.0,0.0,10.0);
			glEnd();
			
		}
	}
	glPopMatrix();

	////////// SET UP 2D VIEWPORT ///////////////
	m_OpenGL.Set_Viewport2D();

	////////// RENDER 2D SCENE //////////////////

	////////// FINISH RENDERING /////////////////
	m_OpenGL.Finish_Render();

	if (rotation >= 358)
		rotation = 0;
	else
		rotation+=2;
	// TODO: Add your specialized code here and/or call the base class
}
