#pragma once
#include <gl/gl.h>
#include <gl/glu.h>

// COpenGL

class COpenGL : public CWnd
{
	DECLARE_DYNAMIC(COpenGL)

public:
	COpenGL();
	virtual ~COpenGL();

	// member variables
	// windows stuff
	HDC		m_hDC;			// The device context for OpenGL
	HGLRC	m_hRC;			// Render Context for OpenGL
	// viewing
	int		m_view_width;
	int		m_view_height;
	float	m_view_aspect;
	float	m_view_fov;
	float	m_view_near_clip;
	float	m_view_far_clip;

	// member functions
	void Init(HDC the_device_context);
	void UnInit(void);
	void Setup(void);

	void Set_Viewport_Size(int width, int height);
	void Set_Viewport3D(void);
	void Set_Viewport2D(void);
	void Finish_Render(void);

protected:
	DECLARE_MESSAGE_MAP()
};


