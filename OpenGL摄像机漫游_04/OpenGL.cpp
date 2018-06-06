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
UINT gPtextureId[16]; // ��ͼ���
GLUquadricObj *gTexture; //��ͼָ��
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
	light0(0, 10, -20, 128);
	gTexture = gluNewQuadric();
	LoadT8(L"aa.bmp", gPtextureId[0]);
	LoadT8(L"bb.BMP", gPtextureId[1]);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			 // ����ˢ�±���ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ˢ�±���
	glLoadIdentity();								 // ���õ�ǰ��ģ�͹۲����

	Play();

	glFlush();										 // ���´���
	SwapBuffers(hDC);								 // �л�������
	r += 0.5f; if (r>360) r = 0; // ��ת��̫�� ������һЩ����
}

void OpenGL::Play()
{
	//Plane(0.0f,8.0f,-50.0f);
	displayScene();
	drawGround();
	picter(4, -4, -10);
	airplane(0, 8, -50);
}

void OpenGL::Plane(float x, float y, float z) // ��Ϸɻ�
{
	glPushMatrix();
	glTranslatef(x, y, z);

	glRotated(-r, 0.0f, 1.0f, 0.0f);
	glTranslatef(20, 0, 0); // �ɻ�����ת�뾶
	glRotatef(30.0f, 0.0f, 0.0f, 1.0f); // ��б�ɻ�, ��Ĵָ�����ߵķ��� ��ס��, �ĸ���ָ�˶��ķ�������ת����
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
	glRotatef(-r * 30, 0.0f, 0.0f, 1.0f);
	auxSolidBox(1.6f, 0.3f, 0.05f); // ������
	glPopMatrix();

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
		0.0, 1.0, 0.0); // ���ﲻҪ��ͷ, ����ֱ�Ӿ���upֵ�ͺ���, һ�������Ҳ������ͷ����
	
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
	glPushMatrix(); // ѹ���ջ
	glTranslatef(x, y, z); // �ɻ��Ķ�λ
	glRotatef(-r, 0.0, 1.0, 0.0); // �ɻ�����ת
	glTranslatef(30, 0, 0); // �ɻ���ƫ��30
	glRotatef(30, 0.0, 0.0, 1.0); // �ɻ���ƫб30��
	//============================================= ������
	glPushMatrix();// ѹ���ջ
	glRotatef(-r * 90, 0.0, 0.0, 1.0); // ����������ת
	glColor3f(0.0, 0.0, 1.0); // ����������ɫ
	Box(1.0f, 0.1f, 0.02f); // ���Ƴ�����, Ҳ����������
	glPopMatrix();// �Ƴ�ջ
	glColor3f(1.0f, 1.0f, 1.0f); // ������ɫ
	glEnable(GL_TEXTURE_2D); // ��������
	glBindTexture(GL_TEXTURE_2D, gPtextureId[1]); // ������....��BUG
	glTranslatef(0.0f, 0.0f, -0.5f); // �ƶ�����
	gluSphere(gTexture, 0.4f, 8, 8); // ����Բ,Ҳ���ǻ�ͷ.
	//============================================= Բ��.����
	glTranslatef(0.0f, -0.0f, -2); // �ƶ�����
	gluCylinder(gTexture, 0.4, 0.4, 2.0, 8, 4); // ����ͼ ��һ��Բ������
	//=====================================================
	glRotatef(-180, 1.0, 0.0, 0.0); // ��ת
	glTranslatef(0.0f, -0.0f, 0.0f); // �ƶ�һ��λ��
	gluCylinder(gTexture, 0.4, 0.1, 1.5, 8, 4); //  ��һ����βԲ׶
	//======================================================
	glBindTexture(GL_TEXTURE_2D, gPtextureId[0]);//
	glTranslatef(0.0f, -0.8f, 1.2f); // λ�õ���
	Box(1.0, 0.05f, 0.3f); // ����, ������
	glTranslatef(0.0f, 0.1f, 0.0f);// λ�õ���
	Box(0.05f, 0.6f, 0.30f);// ����, ������
	//======================================================
	glTranslatef(0.0f, 0.7f, -1.9f); // λ�õ���
	Box(3, 0.05f, 0.5f); // ǰ������
	//======================================================
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
// ���Ƴ�����ר�ú���
void OpenGL::Box(float x, float y, float z)
{
	glPushMatrix();
	glScalef(x, y, z);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);// ǰ
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);// ��
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// ��
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
// �״�+���
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

void OpenGL::CleanUp()//���OpenGL
{
	wglMakeCurrent(hDC, NULL);                       //���OpenGL
	wglDeleteContext(hRC);                           //���OpenGL
}