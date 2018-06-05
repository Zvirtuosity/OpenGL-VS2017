// OpenGL.cpp: implementation of the OpenGL class.
// Edit by zhw in 2018��6��1��17ʱ45��
// E_mail and zhw:zvirtuosity@gmail.com
#include "OpenGL.h"
#include <math.h>
float r;
//////////////////////////////////////////////////////////////////////
//#include "OpenGL.h"
//////////////////////////////////////////////////////////////////////
extern HWND	hWnd;
//////////////////////////////////////////////////////////////////////
OpenGL::OpenGL()
{
}
OpenGL::~OpenGL()
{
	CleanUp();
}
BOOL OpenGL::SetupPixelFormat(HDC hDC0)//��ⰲװOpenGL
{
	int nPixelFormat;					  // ���ص��ʽ
	hDC = hDC0;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
		1,                                // �汾�� 
		PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
		PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
		PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
		PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
		16,                               // 24 λ��ɫ��� 
		0, 0, 0, 0, 0, 0,                 // ������ɫλ 
		0,                                // û�з�͸���Ȼ��� 
		0,                                // ������λλ 
		0,                                // ���ۼӻ��� 
		0, 0, 0, 0,                       // �����ۼ�λ 
		16,                               // 32 λ��Ȼ���     
		0,                                // ��ģ�建�� 
		0,                                // �޸������� 
		PFD_MAIN_PLANE,                   // ���� 
		0,                                // ���� 
		0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	};
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		MessageBox(NULL, L"û�ҵ����ʵ���ʾģʽ", L"Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	SetPixelFormat(hDC, nPixelFormat, &pfd);//���õ�ǰ�豸�����ص��ʽ
	hRC = wglCreateContext(hDC);          //��ȡ��Ⱦ�������
	wglMakeCurrent(hDC, hRC);             //������Ⱦ�������
	return TRUE;
}
void OpenGL::init(int Width, int Height)
{
	glViewport(0, 0, Width, Height);		// ����OpenGL�ӿڴ�С��	
	glMatrixMode(GL_PROJECTION);			// ���õ�ǰ����ΪͶӰ����
	glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
	gluPerspective							// ����͸��ͼ
	(
		54.0f,							    // ͸�ӽ�����Ϊ 45 ��
		(GLfloat)Width / (GLfloat)Height,	// ���ڵĿ���߱�
		0.1f,								// ��Ұ͸�����:����1.0f
		3000.0f							    // ��Ұ͸�����:ʼ��0.1fԶ��1000.0f
	);
	// �������������ƣ���һ���������þ�ͷ��Ƕȣ��ڶ��������ǳ���ȣ�������Զ�����С�
	glMatrixMode(GL_MODELVIEW);				// ���õ�ǰ����Ϊģ����ͼ����
	glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
											//====================================================
}
void OpenGL::Render()//OpenGLͼ�δ���
{
	glClearColor(0.0f, 0.0f, 0.6f, 1.0f);			 // ����ˢ�±���ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ˢ�±���
	glLoadIdentity();								 // ���õ�ǰ��ģ�͹۲����
	Play();
	glFlush();										 // ���´���
	SwapBuffers(hDC);								 // �л�������
	r += 1; if (r>360) r = 0;
}

void OpenGL::Play()
{
	Plane(0.0f,8.0f,-50.0f);
}

void OpenGL::Plane(float x, float y, float z) // ��Ϸɻ�
{
	glPushMatrix();
	glTranslatef(x, y, z);

	glRotated(-r, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	auxSolidBox(1.6f, 0.3f, 0.05f); // ������

	glTranslatef(0.0f, 0.0f, -0.5f); 
	auxSolidSphere(0.5f); // ��ͷ

	glRotatef(90.0f, 1.0f,0.0f, 0.0f);
	glTranslatef(0.0f, -1.0f, 0.0f);
	auxSolidCylinder(0.4f, 2.0f); //����,Բ��

	glRotatef(-270.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 1.0f);
	auxSolidCone(0.4f, 1.5f); // ��β,Բ׶

	glTranslatef(0.0f, -0.5f, 1.2f);
	auxSolidBox(3.0f, 0.05f, 0.5f); // ����

	glTranslatef(0.0f, 0.0f, 0.0f);
	auxSolidBox(0.05f, 1.0f, 0.6f); // ��β��

	glTranslatef(0.0f, 0.7f, -1.9f);
	auxSolidBox(8.0f, 0.05f, 0.7f); // ǰ��

	glPopMatrix();

}

void OpenGL::CleanUp()//���OpenGL
{
	wglMakeCurrent(hDC, NULL);                       //���OpenGL
	wglDeleteContext(hRC);                           //���OpenGL
}