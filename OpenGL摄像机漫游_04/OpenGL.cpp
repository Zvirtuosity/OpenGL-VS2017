// OpenGL.cpp: implementation of the OpenGL class.
// Edit by zhw in 2018年6月1日17时45分
// E_mail and zhw:zvirtuosity@gmail.com
#include "OpenGL.h"
#include <math.h>
float r;
//////////////////////////////////////////////////////////////////////
//#include "OpenGL.h"
//////////////////////////////////////////////////////////////////////
extern HWND	hWnd;
UINT gPtextureId[16]; // 贴图编号
GLUquadricObj *gTexture; //贴图指针
//////////////////////////////////////////////////////////////////////
#define RAND_COORD(x)   ((float)rand()/RAND_MAX * (x))
#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)

OpenGL::OpenGL()
{
	g_eye[0] = 3;//
	g_eye[2] = 2.8;//
	g_angle = -100;
	g_elev = 0;
	gTexture = gluNewQuadric();
	LoadT8(L"aa.bmp", gPtextureId[0]);
	LoadT8(L"bb.BMP", gPtextureId[1]);
}
OpenGL::~OpenGL()
{
	CleanUp();
}

bool OpenGL::LoadT8(LPCWSTR fileName, GLuint &texture)
{
	AUX_RGBImageRec *pImage = nullptr;

	pImage = auxDIBImageLoad(fileName);
	if (pImage == nullptr)
	{
		return false;
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D,
		4,
		pImage->sizeX,
		pImage->sizeY,
		GL_RGB,GL_UNSIGNED_BYTE,
		pImage->data
		);
	free(pImage->data);
	free(pImage);
	return true;
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
	light0(0, 10, -20, 128);
	gTexture = gluNewQuadric();
	LoadT8(L"aa.bmp", gPtextureId[0]);
	LoadT8(L"bb.BMP", gPtextureId[1]);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			 // 设置刷新背景色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 刷新背景
	glLoadIdentity();								 // 重置当前的模型观察矩阵

	Play();

	glFlush();										 // 更新窗口
	SwapBuffers(hDC);								 // 切换缓冲区
	r += 0.5f; if (r>360) r = 0; // 旋转得太快 降低了一些速率
}

void OpenGL::Play()
{
	//Plane(0.0f,8.0f,-50.0f);
	displayScene();
	drawGround();
	picter(4, -4, -10);
	airplane(0, 8, -50);
}

void OpenGL::Plane(float x, float y, float z) // 组合飞机
{
	glPushMatrix();
	glTranslatef(x, y, z);

	glRotated(-r, 0.0f, 1.0f, 0.0f);
	glTranslatef(20, 0, 0); // 飞机的旋转半径
	glRotatef(30.0f, 0.0f, 0.0f, 1.0f); // 倾斜飞机, 大拇指朝着线的方向 握住线, 四根手指运动的方向即是旋转方向
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
	glRotatef(-r * 30, 0.0f, 0.0f, 1.0f);
	auxSolidBox(1.6f, 0.3f, 0.05f); // 螺旋桨
	glPopMatrix();

	glTranslatef(0.0f, 0.0f, -0.5f); 
	auxSolidSphere(0.5f); // 机头

	glRotatef(90.0f, 1.0f,0.0f, 0.0f);
	glTranslatef(0.0f, -1.0f, 0.0f);
	auxSolidCylinder(0.4f, 2.0f); //机身,圆柱

	glRotatef(-270.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 1.0f);
	auxSolidCone(0.4f, 1.5f); // 机尾,圆锥

	glTranslatef(0.0f, -0.5f, 1.2f);
	auxSolidBox(3.0f, 0.05f, 0.5f); // 后翼

	glTranslatef(0.0f, 0.0f, 0.0f);
	auxSolidBox(0.05f, 1.0f, 0.6f); // 后尾垂

	glTranslatef(0.0f, 0.7f, -1.9f);
	auxSolidBox(8.0f, 0.05f, 0.7f); // 前翼

	glPopMatrix();

}

void OpenGL::light0(float x, float y, float z, float a)
{
	GLfloat light_position[] = { x,y,z,a };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

bool OpenGL::displayScene()
{
	float speed = 0.2f; 
	if (KEY_DOWN(VK_SHIFT)) speed *= 4;
	if (KEY_DOWN(VK_LEFT))  g_angle -= speed;
	if (KEY_DOWN(VK_RIGHT)) g_angle += speed;
	rad_xz = float(3.13149 * g_angle / 180.0f);
	if (KEY_DOWN(33)) g_elev += speed;
	if (KEY_DOWN(35)) g_elev -= speed;

	if (KEY_DOWN(VK_UP))
	{
		g_eye[2] += sin(rad_xz) * speed;
		g_eye[0] += cos(rad_xz) * speed;
	}
	if (KEY_DOWN(VK_DOWN))
	{
		g_eye[2] -= sin(rad_xz) * speed;
		g_eye[0] -= cos(rad_xz) * speed;
	}
	g_eye[1] = 1.8f;
	g_look[0] = g_eye[0] + cos(rad_xz);
	g_look[2] = g_eye[2] + sin(rad_xz);
	g_look[1] = g_eye[1];
	gluLookAt(g_eye[0], g_eye[1], g_eye[2],
		g_look[0], g_look[1] + g_elev, g_look[2],
		0.0, 1.0, 0.0); // 这里不要歪头, 所以直接就是up值就好了, 一般摄像机也很少歪头看的
	
	return true;
}

void OpenGL::drawGround()
{
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_BLEND);
	glPushMatrix();
	glColor3f(0.5f, 0.7f, 1.0f);
	glTranslatef(0, 0.0f, 0);
	int size0 = (int)(MAP * 2);
	glBegin(GL_LINES);
	for (int x = -size0; x < size0; x += 4)
	{
		glVertex3i(x, 0, -size0); glVertex3i(x, 0, size0);
	}
	for (int z = -size0; z < size0; z += 4)
	{
		glVertex3i(-size0, 0, z); glVertex3i(size0, 0, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glPopAttrib();
}

void OpenGL::airplane(float x, float y, float z)
{
	glPushMatrix(); // 压入堆栈
	glTranslatef(x, y, z); // 飞机的定位
	glRotatef(-r, 0.0, 1.0, 0.0); // 飞机的旋转
	glTranslatef(30, 0, 0); // 飞机的偏移30
	glRotatef(30, 0.0, 0.0, 1.0); // 飞机的偏斜30度
	//============================================= 螺旋桨
	glPushMatrix();// 压入堆栈
	glRotatef(-r * 90, 0.0, 0.0, 1.0); // 螺旋桨的旋转
	glColor3f(0.0, 0.0, 1.0); // 螺旋桨的颜色
	Box(1.0f, 0.1f, 0.02f); // 绘制长方体, 也就是螺旋桨
	glPopMatrix();// 推出栈
	glColor3f(1.0f, 1.0f, 1.0f); // 机身颜色
	glEnable(GL_TEXTURE_2D); // 启用纹理
	glBindTexture(GL_TEXTURE_2D, gPtextureId[1]); // 绑定纹理....有BUG
	glTranslatef(0.0f, 0.0f, -0.5f); // 移动画笔
	gluSphere(gTexture, 0.4f, 8, 8); // 绘制圆,也就是机头.
	//============================================= 圆柱.机身
	glTranslatef(0.0f, -0.0f, -2); // 移动画笔
	gluCylinder(gTexture, 0.4, 0.4, 2.0, 8, 4); // 绑定贴图 画一个圆柱机身
	//=====================================================
	glRotatef(-180, 1.0, 0.0, 0.0); // 旋转
	glTranslatef(0.0f, -0.0f, 0.0f); // 移动一定位置
	gluCylinder(gTexture, 0.4, 0.1, 1.5, 8, 4); //  画一个机尾圆锥
	//======================================================
	glBindTexture(GL_TEXTURE_2D, gPtextureId[0]);//
	glTranslatef(0.0f, -0.8f, 1.2f); // 位置调整
	Box(1.0, 0.05f, 0.3f); // 后翼, 长方体
	glTranslatef(0.0f, 0.1f, 0.0f);// 位置调整
	Box(0.05f, 0.6f, 0.30f);// 后垂翼, 长方体
	//======================================================
	glTranslatef(0.0f, 0.7f, -1.9f); // 位置调整
	Box(3, 0.05f, 0.5f); // 前翼长方体
	//======================================================
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
// 绘制长方体专用函数
void OpenGL::Box(float x, float y, float z)
{
	glPushMatrix();
	glScalef(x, y, z);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);// 前
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 后
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);// 上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 下
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);// 左
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 右
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
// 雷达+火箭
void OpenGL::picter(float x, float y, float z) 
{
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glTranslatef(x, y + 0.5f, z);
	glColor3f(0.0f, 1.0f, 0.2f);
	auxSolidCube(1);
	glTranslatef(0.0f, 0.8f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	auxSolidBox(.2f, 1.3f, .2f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x, y + 2.5f, z);
	glRotatef(r - 90, 0.0, 1.0, 0.0);
	//=======================================
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(45, 1.0, 0.0, 0.0);
	auxWireCone(1.5, 0.6f);
	//=======================================
	glRotatef(180, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, 0.0f, -0.7f);
	auxWireCone(0.2f, 2.0f);
	glColor3f(FRAND, 0, 0);
	glTranslatef(0.0f, 0.0f, 2.0f);
	auxSolidSphere(0.1f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y + 10.0f, z);
	glRotatef(r, 0.0, 1.0, 0.0);
	glTranslatef(15, 0, 0);
	//=============================================
	glColor3f(1.0f, 0.0f, 0.0f);
	glRotatef(180, 0.0, 1.0, 0.0);
	auxSolidCone(.2, 0.6);
	//=============================================
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, -1.0f, 0);
	auxSolidCylinder(.2f, 1);
	glRotatef(-270, 1.0, 0.0, 0.0);
	glColor3f(FRAND + .6f, 0.2f, 0.0f);
	glTranslatef(0.0f, -0.0f, -0.2f);
	auxSolidCone(.2, 1.5);
	glPopMatrix();
	glPopAttrib();
	
}

void OpenGL::CleanUp()//清除OpenGL
{
	wglMakeCurrent(hDC, NULL);                       //清除OpenGL
	wglDeleteContext(hRC);                           //清除OpenGL
}