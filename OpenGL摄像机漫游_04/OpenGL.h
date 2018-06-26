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
#include "glaux.h"
#include "Wingdi.h"
#pragma once
//#endif // _MSC_VER > 1000

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
class OpenGL
{
public:	OpenGL();
		virtual ~OpenGL();
public:

	HDC		hDC;			// GDI�豸������
	HGLRC	hRC;		    // ������ɫ������
	double g_eye[3]; // ���������λ��(�۾�λ��)
	double g_look[3]; // ��������, Ҳ�������ǿ�������?
	float rad_xz; 
	float g_angle;
	float g_elev;
	bool    LoadT8(LPCWSTR fileName, GLuint & texture);
	BOOL	SetupPixelFormat(HDC hDC);
	void	init(int Width, int Height);
	void	Render();
	void    Play();
	void    Plane(float x, float y, float z);
	void    light0(float x, float y, float z, float a);
	bool    displayScene();
	void    drawGround();
	void    airplane(float x, float y, float z);
	void    Box(float x, float y, float z);
	void    picter(float x, float y, float z);
	void	CleanUp();
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000)?1:0)
#define MAP		40//	MAP_W*MAP_SCALE/2
};

//#endif // !defined(AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_)
