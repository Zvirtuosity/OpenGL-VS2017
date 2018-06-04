// OpenGL.cpp: implementation of the OpenGL class.
// 程序设计：唐明理	2005.2  Edit by zhw in 2018年6月1日17时45分
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
BOOL OpenGL::SetupPixelFormat(HDC hDC0)//检测安装OpenGL
{
	int nPixelFormat;					  // 象素点格式
	hDC = hDC0;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
		1,                                // 版本号 
		PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
		PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
		PFD_DOUBLEBUFFER,                 // 双缓存模式 
		PFD_TYPE_RGBA,                    // RGBA 颜色模式 
		16,                               // 24 位颜色深度 
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
		0,                                // 没有非透明度缓存 
		0,                                // 忽略移位位 
		0,                                // 无累加缓存 
		0, 0, 0, 0,                       // 忽略累加位 
		16,                               // 32 位深度缓存     
		0,                                // 无模板缓存 
		0,                                // 无辅助缓存 
		PFD_MAIN_PLANE,                   // 主层 
		0,                                // 保留 
		0, 0, 0                           // 忽略层,可见性和损毁掩模 
	};
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		MessageBox(NULL, L"没找到合适的显示模式", L"Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	SetPixelFormat(hDC, nPixelFormat, &pfd);//设置当前设备的像素点格式
	hRC = wglCreateContext(hDC);          //获取渲染描述句柄
	wglMakeCurrent(hDC, hRC);             //激活渲染描述句柄
	return TRUE;
}
void OpenGL::init(int Width, int Height)
{
	glViewport(0, 0, Width, Height);		// 设置OpenGL视口大小。	
	glMatrixMode(GL_PROJECTION);			// 设置当前矩阵为投影矩阵。
	glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵
	gluPerspective							// 设置透视图
	(
		54.0f,							    // 透视角设置为 45 度
		(GLfloat)Width / (GLfloat)Height,	// 窗口的宽与高比
		0.1f,								// 视野透视深度:近点1.0f
		3000.0f							    // 视野透视深度:始点0.1f远点1000.0f
	);
	// 这和照象机很类似，第一个参数设置镜头广角度，第二个参数是长宽比，后面是远近剪切。
	glMatrixMode(GL_MODELVIEW);				// 设置当前矩阵为模型视图矩阵
	glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵
											//====================================================
}
void OpenGL::Render()//OpenGL图形处理
{
	glClearColor(0.0f, 0.0f, 0.6f, 1.0f);			 // 设置刷新背景色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 刷新背景
	glLoadIdentity();								 // 重置当前的模型观察矩阵
	Play();
	glFlush();										 // 更新窗口
	SwapBuffers(hDC);								 // 切换缓冲区
	r += 1; if (r>360) r = 0;
}

void OpenGL::Play()
{
	// 图形显示
	glPushMatrix(); // 注意, push和pop必须一一对应, 否则会出现一些奇怪的问题
	glPointSize(4);
	glTranslatef(-5, 4, -13);
	glRotatef(r, 1.0, 1.0, 1.0);
	glColor3f(1.0f, 0, 0);
	glBegin(GL_POINTS); // 画点
	glVertex3f(0.0f, 1.0f, -1.0f); //a点
	glVertex3f(-1.0f, -1.0f, 0.0f);//b点
	glVertex3f(1.0f, -1.0f, 0.0f); //c点
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, -13); 
	glRotatef(r, 1.0, 1.0, 1.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP); // 画线
	glVertex3f(0.0f, 1.0f, -1.0f); //a点
	glVertex3f(-1.0f, -1.0f, 0.0f);//b点
	glVertex3f(1.0f, -1.0f, 0.0f); //c点
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 4, -13);
	glRotatef(r, 1.0, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON); // 画面
	glVertex3f(0.0f, 1.0f, -1.0f);  //a点
	glVertex3f(-1.0f, -1.0f, 0.0f); //b点
	glVertex3f(1.0f, -1.0f, 0.0f);  //c点
	glEnd();
	glPopMatrix();

	glPushMatrix(); 
	glTranslatef(-5, 0, -13);
	glRotated(r, 1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON); // 画多边形
	glVertex3f(0.0f, 0.0f, 0.0f); //a点
	glVertex3f(1.0f, 0.0f, 0.0f); //b点
	glVertex3f(1.0f, 0.0f, -1.0f);//c点
	glVertex3f(0.0f, 0.0f, -1.0f);//d点
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -13);
	glRotated(r, 1.0f, 1.0f, 1.0f);
	glColor3f(1, 0, 0);
	glBegin(GL_QUAD_STRIP); //画正方体
	glVertex3f(0.0f, 0.0f, 0.0f); //a0点
	glVertex3f(0.0f, 1.0f, 0.0f); //a1点
	glVertex3f(1.0f, 0.0f, 0.0f); //b0点
	glVertex3f(1.0f, 1.0f, 0.0f); //b1点
	glVertex3f(1.0f, 0.0f, -1.0f);//c0点
	glVertex3f(1.0f, 1.0f, -1.0f);//c1点
	glVertex3f(0.0f, 0.0f, -1.0f);//d0点
	glVertex3f(0.0f, 1.0f, -1.0f);//d1点
	glVertex3f(0.0f, 0.0f, 0.0f); //a0点
	glVertex3f(0.0f, 1.0f, 0.0f); //a1点
	glEnd();
	glBegin(GL_POLYGON);//补上正方体的一面
	glVertex3f(0.0f, 0.0f, 0.0f);//a0点
	glVertex3f(1.0f, 0.0f, 0.0f);//b0点
	glVertex3f(1.0f, 0.0f, -1.0f);//c0点
	glVertex3f(0.0f, 0.0f, -1.0f);//d0点
	glVertex3f(0.0f, 1.0f, 0.0f);//a1点
	glVertex3f(1.0f, 1.0f, 0.0f);//b1点
	glVertex3f(1.0f, 1.0f, -1.0f);//c1点
	glVertex3f(0.0f, 1.0f, -1.0f);//d1点
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
	auxSolidCone(1, 1); // 画一个圆锥
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, -4, -13); 
	glRotatef(r, 1.0, 1.0, 1.0);
	glColor3f(0.4f, 0.4f, 0.4f); 
	auxWireTeapot(1); // 画一个茶壶
	glPopMatrix();
}

void OpenGL::CleanUp()//清除OpenGL
{
	wglMakeCurrent(hDC, NULL);                       //清除OpenGL
	wglDeleteContext(hRC);                           //清除OpenGL
}