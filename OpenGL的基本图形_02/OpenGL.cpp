// OpenGL.cpp: implementation of the OpenGL class.
// ������ƣ�������	2005.2  Edit by zhw in 2018��6��1��17ʱ45��
// E_mail cqtml@163.com
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
	// ͼ����ʾ
	glPushMatrix(); // ע��, push��pop����һһ��Ӧ, ��������һЩ��ֵ�����
	glPointSize(4);
	glTranslatef(-5, 4, -13);
	glRotatef(r, 1.0, 1.0, 1.0);
	glColor3f(1.0f, 0, 0);
	glBegin(GL_POINTS); // ����
	glVertex3f(0.0f, 1.0f, -1.0f); //a��
	glVertex3f(-1.0f, -1.0f, 0.0f);//b��
	glVertex3f(1.0f, -1.0f, 0.0f); //c��
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, -13); 
	glRotatef(r, 1.0, 1.0, 1.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP); // ����
	glVertex3f(0.0f, 1.0f, -1.0f); //a��
	glVertex3f(-1.0f, -1.0f, 0.0f);//b��
	glVertex3f(1.0f, -1.0f, 0.0f); //c��
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 4, -13);
	glRotatef(r, 1.0, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON); // ����
	glVertex3f(0.0f, 1.0f, -1.0f);  //a��
	glVertex3f(-1.0f, -1.0f, 0.0f); //b��
	glVertex3f(1.0f, -1.0f, 0.0f);  //c��
	glEnd();
	glPopMatrix();

	glPushMatrix(); 
	glTranslatef(-5, 0, -13);
	glRotated(r, 1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON); // �������
	glVertex3f(0.0f, 0.0f, 0.0f); //a��
	glVertex3f(1.0f, 0.0f, 0.0f); //b��
	glVertex3f(1.0f, 0.0f, -1.0f);//c��
	glVertex3f(0.0f, 0.0f, -1.0f);//d��
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -13);
	glRotated(r, 1.0f, 1.0f, 1.0f);
	glColor3f(1, 0, 0);
	glBegin(GL_QUAD_STRIP); //��������
	glVertex3f(0.0f, 0.0f, 0.0f); //a0��
	glVertex3f(0.0f, 1.0f, 0.0f); //a1��
	glVertex3f(1.0f, 0.0f, 0.0f); //b0��
	glVertex3f(1.0f, 1.0f, 0.0f); //b1��
	glVertex3f(1.0f, 0.0f, -1.0f);//c0��
	glVertex3f(1.0f, 1.0f, -1.0f);//c1��
	glVertex3f(0.0f, 0.0f, -1.0f);//d0��
	glVertex3f(0.0f, 1.0f, -1.0f);//d1��
	glVertex3f(0.0f, 0.0f, 0.0f); //a0��
	glVertex3f(0.0f, 1.0f, 0.0f); //a1��
	glEnd();
	glBegin(GL_POLYGON);//�����������һ��
	glVertex3f(0.0f, 0.0f, 0.0f);//a0��
	glVertex3f(1.0f, 0.0f, 0.0f);//b0��
	glVertex3f(1.0f, 0.0f, -1.0f);//c0��
	glVertex3f(0.0f, 0.0f, -1.0f);//d0��
	glVertex3f(0.0f, 1.0f, 0.0f);//a1��
	glVertex3f(1.0f, 1.0f, 0.0f);//b1��
	glVertex3f(1.0f, 1.0f, -1.0f);//c1��
	glVertex3f(0.0f, 1.0f, -1.0f);//d1��
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, -13);
	glRotated(r, 1, 1, 1);
	glColor3f(1, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (int i=0; i <= 390; i+=30)
	{
		float  p = i*3.14f / 180;
		glVertex3f(sin(p), cos(p), 0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -4, -13);
	glRotated(r,1, 1, 1);
	glColor3f(1, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (int i=0; i <=390; i+=30)
	{
		float p = i * 3.14 / 180;
		glVertex3f(sin(p) / 2, cos(p) / 2, 1.0f);
		glVertex3f(sin(p) / 2, cos(p) / 2, 0.0f);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix(); 
	glTranslatef(0, -4, -13); 
	glRotatef(r, 1.0, 1.0, 1.0);
	glColor3f(0.7f, 0.7f, 0.7f);
	auxSolidCone(1, 1); // ��һ��Բ׶
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, -4, -13); 
	glRotatef(r, 1.0, 1.0, 1.0);
	glColor3f(0.4f, 0.4f, 0.4f); 
	auxWireTeapot(1); // ��һ�����
	glPopMatrix();
}

void OpenGL::CleanUp()//���OpenGL
{
	wglMakeCurrent(hDC, NULL);                       //���OpenGL
	wglDeleteContext(hRC);                           //���OpenGL
}