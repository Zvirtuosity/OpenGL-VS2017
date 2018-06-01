// OpenGL.h: interface for the OpenGL class.
//
//////////////////////////////////////////////////////////////////////

// ע��: �����õĶ���ȫ������ע�͵���, ����Ҫ�Ļ��Լ���һ�� by zhw,2018��6��1��16ʱ55��
//#if !defined(AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_)
//#define AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_
//
//#if _MSC_VER > 1000
#include "windows.h"
#include "gl/GL.h"
#include "gl/GLU.h"
#include "Wingdi.h"
#pragma once
//#endif // _MSC_VER > 1000

class OpenGL
{
public:	OpenGL();
		virtual ~OpenGL();
public:

	HDC		hDC;			// GDI�豸������
	HGLRC	hRC;		    // ������ɫ������
	BOOL	SetupPixelFormat(HDC hDC);
	void	init(int Width, int Height);
	void	Render();
	void	CleanUp();
};

//#endif // !defined(AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_)
