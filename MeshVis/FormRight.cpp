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
	scale = 1;
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
	OutputDebugString(_T("\nTHE RENDER SCENE METHOD WAS CALLED\n"));
	
	m_OpenGL.Init( (GetDC())->m_hDC );
	// TODO: Add your control notification handler code here
		////////// CLEAR BUFFERS ////////////////////
	//glClearColor(0.5f, 0.6f, 0.73f, 0.0f);//This line can be used to change the background color of the OGL window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	////////// SET UP 3D VIEWPORT ///////////////
	m_OpenGL.Set_Viewport3D();
	//gluLookAt(0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);//The original line
	/*
	float x =pDoc->GV->getMaxX();
	float y = pDoc->GV->getMaxY();
	float z = pDoc->GV->getMaxZ();
	if(x < 1)
		x += 0.1;
	else
		x+= 10;
	if(pDoc->GV->getMaxY()< 1)
		y += + 0.1;
	else y += 10;
	if(pDoc->GV->getMaxZ()< 1)
		z += 0.1;
	else z += 10;
	gluLookAt(x,y,z,0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	*/
	

	glPushMatrix();
	gluLookAt(0, 0, cameraZ, 0, 0, 0.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(trans_x, trans_y, trans_z);
	glRotatef(rotate_x,1,0,0);
	glRotatef(rotate_y,0,1,0);
	glRotatef(rotate_z,0,0,1);
	{
		if(pDoc->GV->showNodes())
		{
			OutputDebugString(_T("Node Viewing is turned on.\n"));
			int n = pDoc->GV->getNumNode();
			CString cn;
			cn.Format(_T("nodes:%d\n"),n);
			OutputDebugString(cn);
			glPointSize(2);
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
				for(int j = 0; j<pDoc->GV->getNumNode(); j++)
				{
					//std::string node = pDoc->GV->getNode(j)->toString();
					Node * tn = pDoc->GV->getNode(j);
					int id = tn->getID();
					double x = tn->getX()*scale; 
					double y = tn->getY()*scale;
					double z = tn->getZ()*scale;
					glVertex3d(x,y,z);		//Scaled by 100 for testing
				}
			glEnd();
		}

	
		bool polys = false;
		if(polys)
		{
		int e = pDoc->GV->getNumElements();
		for(int i = 0; i < e; i++)
		{
			std::vector<int> elementI = *pDoc->GV->getElement(i);
			//OutputDebugString(_T("\n got the element.\n"));
			int nodes = elementI[2];
			CString num; 
			num.Format(_T("\nElement:%d has %d nodes:\n"), i, nodes);
			OutputDebugString(num);
			switch (nodes)
			{
			case 2: 
				{
					//OutputDebugString(_T("\nElement of type 2 (Line/WIRE)\n"));
					glColor3f(0.0, 1.0, 0.0);//GREEN
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
					glColor3f(0.0, 1.0, 1.0);//PURPLE
					/*for(int k =0; k < nodes; k++)//This may need to be changed to counter clock wise initialization meaning 0,1,3,2 instead of 0,1,2,3,
					{
						glBegin(GL_QUADS);
						int nodeID = elementI[k+3];
						Node * tn = pDoc->GV->getNode(nodeID);
						double x =tn->getX()*scale;
						double y = tn->getY()*scale;
						double z = tn->getZ()*scale;
						glVertex3d(x,y,z);
						glEnd();
					}*/
					//CString qa;
					glBegin(GL_QUADS);
					std::vector<double> tempv = pDoc->GV->getNodeVec(i, 0, scale);
					//qa.Format(_T("\ni: %d x:%f y:%f z:%f\n"),i,tempv[0], tempv[1], tempv[2]);
					//OutputDebugString(qa);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					break;
				}
			case 8:
				{
					//OutputDebugString(_T("\nThis will be a first order cube."));
					 
					glColor3f(1.0, 1.0, 0.0); //YELLOW
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
					//OutputDebugString(_T("\nThis will be a 2nd order plate."));

					glColor3f(0.0, 0.0, 1.0); ///BLUE
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
			case 27: //27 node element, 2nd order 1 node represents center
				{
					//OutputDebugString(_T("\nThis will be a 2nd order cube."));
					
					glColor3f(0.2, 1.0, 1.0); //not exactly sure what color this is
					glBegin(GL_QUADS);//1 IDs: 0,1,4,3
					std::vector<double> tempv = pDoc->GV->getNodeVec(i, 0, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//2 IDs: 1,2,5,4
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//3 IDs: 3,4,7,6
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					
					glBegin(GL_QUADS);//4 IDs: 4,5,8,7
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 8, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//5 IDs: 11,2,5,14
					tempv = pDoc->GV->getNodeVec(i, 11, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 14, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//6 IDs: 20.11.14.23
					tempv = pDoc->GV->getNodeVec(i, 20, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 11, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 14, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 23, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//7 IDs: 14,5,8,17
					tempv = pDoc->GV->getNodeVec(i, 14, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 8, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 17, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//8 IDs: 23,14,17,26
					tempv = pDoc->GV->getNodeVec(i, 23, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 14, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 17, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 26, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//9 IDs: 18,19,22,21
					tempv = pDoc->GV->getNodeVec(i, 18, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 19, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 22, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 21, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//10 IDs: 19,20,23,22
					tempv = pDoc->GV->getNodeVec(i, 19, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 20, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 23, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 22, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//11 IDs: 21,22,25,24
					tempv = pDoc->GV->getNodeVec(i, 21, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 22, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 25, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 24, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//12 IDs: 22,23,26,25
					tempv = pDoc->GV->getNodeVec(i, 22, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 23, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 26, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 25, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//13 IDs: 0,9,12,3
					tempv = pDoc->GV->getNodeVec(i, 0, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 9, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 12, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//14 IDs: 9,18,21,12
					tempv = pDoc->GV->getNodeVec(i, 9, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 18, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 21, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 12, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//15 IDs: 12,3,6,15
					tempv = pDoc->GV->getNodeVec(i, 12, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 15, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//16 IDs: 12,21,24,15
					tempv = pDoc->GV->getNodeVec(i, 12, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 21, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 24, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 15, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//17 IDs: 0,1,10,9
					tempv = pDoc->GV->getNodeVec(i, 0, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 10, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 9, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//18 IDs: 1,2,11,10
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 11, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 10, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//19 IDs: 10,11,20,19
					tempv = pDoc->GV->getNodeVec(i, 10, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 11, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 20, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 19, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//20 IDs: 9,10,19,18
					tempv = pDoc->GV->getNodeVec(i, 9, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 10, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 19, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 18, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//21 IDs: 7,8,17,16
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 8, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 17, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 16, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//22 IDs: 6,8,16,15
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 8, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 16, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 15, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//23 IDs: 16,17,26,25
					tempv = pDoc->GV->getNodeVec(i, 16, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 17, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 26, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 25, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_QUADS);//24 IDs: 15,16,25,24
					tempv = pDoc->GV->getNodeVec(i, 15, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 16, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 25, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 24, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					break;
				}
			default: 
				OutputDebugString(_T("\nTHE FOLLOWING LINE SHOULD NEVER PRINT AT THIS POINT:\nThis element type is not implemented yet."));
				
			}//end switch
		}//end for loop
		}//end if
		bool wireframe = true;
		if(wireframe)
		{
		int e = pDoc->GV->getNumElements();
		for(int i = 0; i < e; i++)
		{
			std::vector<int> elementI = *pDoc->GV->getElement(i);
			//OutputDebugString(_T("\n got the element.\n"));
			int nodes = elementI[2];
			CString num; 
			//num.Format(_T("\nElement:%d has %d nodes:\n"), i, nodes);
			//OutputDebugString(num);
			switch (nodes)
			{
			case 2: 
				{
					//OutputDebugString(_T("\nElement of type 2 (Line/WIRE)\n"));
					glColor3f(0.0, 1.0, 0.0);//GREEN
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
					glColor3f(1.0, 1.0, 0.0);//yellow frame on purple
					/*for(int k =0; k < nodes; k++)//This may need to be changed to counter clock wise initialization meaning 0,1,3,2 instead of 0,1,2,3,
					{
						glBegin(GL_QUADS);
						int nodeID = elementI[k+3];
						Node * tn = pDoc->GV->getNode(nodeID);
						double x =tn->getX()*scale;
						double y = tn->getY()*scale;
						double z = tn->getZ()*scale;
						glVertex3d(x,y,z);
						glEnd();
					}*/
					glBegin(GL_LINE_LOOP);
					//CString qa;
					std::vector<double> tempv = pDoc->GV->getNodeVec(i, 0, scale);
					//qa.Format(_T("\ni: %d x:%f y:%f z:%f\n"),i,tempv[0], tempv[1], tempv[2]);
					//OutputDebugString(qa);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					//qa.Format(_T("\ni: %d x:%f y:%f z:%f\n"),i,tempv[0], tempv[1], tempv[2]);
					//OutputDebugString(qa);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					//qa.Format(_T("\ni: %d x:%f y:%f z:%f\n"),i,tempv[0], tempv[1], tempv[2]);
					//OutputDebugString(qa);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					//qa.Format(_T("\ni: %d x:%f y:%f z:%f\n"),i,tempv[0], tempv[1], tempv[2]);
					//OutputDebugString(qa);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					break;
				}
			case 8:
				{
					//OutputDebugString(_T("\nThis will be a first order cube.8"));
					 
					glColor3f(0.0, 0.0, 1.0); //blue frame on YELLOW
					//Right side quad:0,1,3,2
					glBegin(GL_LINE_LOOP);
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
					glBegin(GL_LINE_LOOP);
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
					glBegin(GL_LINE_LOOP);
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
					glBegin(GL_LINE_LOOP);
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
					glBegin(GL_LINE_LOOP);
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
					glBegin(GL_LINE_LOOP);
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
					//OutputDebugString(_T("\nThis will be a 2nd order plate.9"));

					glColor3f(1.0, 0.0, 0.0); ///red frame on BLUE
					//0,3,4,1
					glBegin(GL_LINE_LOOP);
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
					glBegin(GL_LINE_LOOP);
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
					glBegin(GL_LINE_LOOP);
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
					glBegin(GL_LINE_LOOP);
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
			case 27: //27 node element, 2nd order 1 node represents center
				{
					//OutputDebugString(_T("\nThis will be a 2nd order cube.27"));
					
					glColor3f(1.0, 0.5, 0.1); //orange on cyan? not exactly sure what color this is
					glBegin(GL_LINE_LOOP);//1 IDs: 0,1,4,3
					std::vector<double> tempv = pDoc->GV->getNodeVec(i, 0, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//2 IDs: 1,2,5,4
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//3 IDs: 3,4,7,6
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					
					glBegin(GL_LINE_LOOP);//4 IDs: 4,5,8,7
					tempv = pDoc->GV->getNodeVec(i, 4, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 8, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//5 IDs: 11,2,5,14
					tempv = pDoc->GV->getNodeVec(i, 11, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 14, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//6 IDs: 20.11.14.23
					tempv = pDoc->GV->getNodeVec(i, 20, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 11, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 14, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 23, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//7 IDs: 14,5,8,17
					tempv = pDoc->GV->getNodeVec(i, 14, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 5, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 8, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 17, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//8 IDs: 23,14,17,26
					tempv = pDoc->GV->getNodeVec(i, 23, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 14, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 17, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 26, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//9 IDs: 18,19,22,21
					tempv = pDoc->GV->getNodeVec(i, 18, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 19, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 22, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 21, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//10 IDs: 19,20,23,22
					tempv = pDoc->GV->getNodeVec(i, 19, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 20, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 23, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 22, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//11 IDs: 21,22,25,24
					tempv = pDoc->GV->getNodeVec(i, 21, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 22, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 25, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 24, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//12 IDs: 22,23,26,25
					tempv = pDoc->GV->getNodeVec(i, 22, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 23, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 26, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 25, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//13 IDs: 0,9,12,3
					tempv = pDoc->GV->getNodeVec(i, 0, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 9, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 12, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//14 IDs: 9,18,21,12
					tempv = pDoc->GV->getNodeVec(i, 9, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 18, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 21, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 12, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//15 IDs: 12,3,6,15
					tempv = pDoc->GV->getNodeVec(i, 12, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 3, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 15, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//16 IDs: 12,21,24,15
					tempv = pDoc->GV->getNodeVec(i, 12, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 21, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 24, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 15, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//17 IDs: 0,1,10,9
					tempv = pDoc->GV->getNodeVec(i, 0, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 10, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 9, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//18 IDs: 1,2,11,10
					tempv = pDoc->GV->getNodeVec(i, 1, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 2, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 11, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 10, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//19 IDs: 10,11,20,19
					tempv = pDoc->GV->getNodeVec(i, 10, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 11, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 20, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 19, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//20 IDs: 9,10,19,18
					tempv = pDoc->GV->getNodeVec(i, 9, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 10, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 19, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 18, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//21 IDs: 7,8,17,16
					tempv = pDoc->GV->getNodeVec(i, 7, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 8, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 17, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 16, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//22 IDs: 6,8,16,15
					tempv = pDoc->GV->getNodeVec(i, 6, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 8, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 16, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 15, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//23 IDs: 16,17,26,25
					tempv = pDoc->GV->getNodeVec(i, 16, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 17, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 26, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 25, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();

					glBegin(GL_LINE_LOOP);//24 IDs: 15,16,25,24
					tempv = pDoc->GV->getNodeVec(i, 15, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 16, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 25, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					tempv = pDoc->GV->getNodeVec(i, 24, scale);
					glVertex3d(tempv[0], tempv[1], tempv[2]);
					glEnd();
					break;
				}
			default: 
				OutputDebugString(_T("\nTHE FOLLOWING LINE SHOULD NEVER PRINT AT THIS POINT:\nThis element type is not implemented yet."));
				
			}//end switch
		}//End of for
		}//end if
	}
	glPopMatrix();

	//OutputDebugString(_T("\ndone creating elements.\n"));

	if(pDoc->GV->showAxes())
	{
		glPushMatrix();
		gluLookAt(0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
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





	
	//OutputDebugString(_T("\nThe visualization should rotate\n"));
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
	static bool sized = false;
	CPaintDC dc(this); // device context for painting
	
	if(!init)
	{
		rotate_x=rotate_y=rotate_z=0;
		trans_x=trans_y=trans_z=0;
		init = true;
	}

	CMeshVisDoc *pDoc=(CMeshVisDoc *)GetDocument();
	if(pDoc->GV->getFileOpen() && !sized)
	{
		autoSizing();
		sized = true;
	}
	RenderScene();

	
}

void CFormRight::autoSizing()
{
	CMeshVisDoc *pDoc=(CMeshVisDoc *)GetDocument();
	double maxX = pDoc->GV->getMaxX();
	double minX = pDoc->GV->getMinX();
	double maxY = pDoc->GV->getMaxY();
	double minY = pDoc->GV->getMinY();
	double maxZ = pDoc->GV->getMaxZ();

	
	float scaleX = 20.0 / (maxX - minX);
	float scaleY = 20.0 / (maxY - minY);
	float optimalScale = scaleX<scaleY?scaleX:scaleY;

	cameraZ=50;
	if(maxZ*optimalScale>cameraZ) cameraZ+=5;

	//trans_x = -(maxX+minX)*optimalScale/2;
	//trans_y = -(maxY+minY)*optimalScale/2;

	scale = optimalScale;
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
