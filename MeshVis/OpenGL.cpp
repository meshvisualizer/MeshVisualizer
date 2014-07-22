// OpenGL.cpp : implementation file
//

#include "stdafx.h"
//#include "MFC Test.h"
#include "OpenGL.h"


// COpenGL

IMPLEMENT_DYNAMIC(COpenGL, CWnd)

COpenGL::COpenGL()
{
	HDC		m_hDC = NULL;
	HGLRC	m_hRC = NULL;
	
	m_view_far_clip = 3000.0f;
	m_view_near_clip = 5.0f;
	m_view_fov = 50.0f;
}

COpenGL::~COpenGL()
{

}

void COpenGL::Init(HDC the_device_context)
{
	// Initialise OpenGL

	// Get a DC for the OpenGL render window
	m_hDC = the_device_context;

	// Set the pixel format for this DC
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof (PIXELFORMATDESCRIPTOR),	// strcut size 
		1,						// Version number
		PFD_DRAW_TO_WINDOW |    // Flags, draw to a window,
		PFD_SUPPORT_OPENGL |    // use OpenGL
		PFD_DOUBLEBUFFER,		// double buffered
		PFD_TYPE_RGBA,          // RGBA pixel values
		32,                     // 32-bit color
		0, 0, 0,                // RGB bits & shift sizes.
		0, 0, 0,                // Don't care about them
		0, 0,                   // No alpha buffer info
		0, 0, 0, 0, 0,          // No accumulation buffer
		32,                     // 32-bit depth buffer
		0,                      // No stencil buffer
		0,                      // No auxiliary buffers
		PFD_MAIN_PLANE,         // Layer type
		0,                      // Reserved (must be 0)
		0,                      // No layer mask
		0,                      // No visible mask
		0                       // No damage mask
	};

    int nMyPixelFormatID = ChoosePixelFormat( m_hDC, &pfd );

    SetPixelFormat( m_hDC, nMyPixelFormatID, &pfd );

	// get a render context for OpenGL
	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent (m_hDC, m_hRC);
}

void COpenGL::UnInit()
{
	// Tell windows we don't want to use OpenGL anymore
	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hRC);
}

void COpenGL::Set_Viewport_Size(int width, int height)
{
	// update the window properties

	// prevent divide by zero
	if (height == 0) height = 1;

	m_view_width = width;
	m_view_height = height;

	m_view_aspect = width/height;
}

void COpenGL::Set_Viewport3D()
{
	// set up the viewing transforms for a 3D view
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	// a perspective-view matrix...
	gluPerspective(
		m_view_fov,			// Field-of-view angle
		m_view_aspect,		// Aspect ratio of view volume
		m_view_near_clip,	// Distance to near clipping plane
		m_view_far_clip );	// Distance to far clipping plane

	glViewport( 0, 0, m_view_width, m_view_height );
	//glViewport( 0, 0, 1200, 500 );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void COpenGL::Set_Viewport2D()
{
	// Setup the viewing transformations for 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0,m_view_width,m_view_height,0);
	glViewport(0, 0, m_view_width, m_view_height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void COpenGL::Finish_Render()
{
	glFlush();
	SwapBuffers(m_hDC);
}

void COpenGL::Setup()
{
	// put generic OpenGL code here

	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Set OpenGL state variables
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glFrontFace(GL_CCW);
}


BEGIN_MESSAGE_MAP(COpenGL, CWnd)
END_MESSAGE_MAP()



// COpenGL message handlers


