# OpenGL-VS2017
    较为详细的注释跟随代码。
## 3DFrame_01
    OpenGL框架，直接可以可运行。
    glViewport(0， 0， Width， Height);
    glMatrixMode(GL_PROJECTION);
## OpenGL的基本图形_02
    这一部分内容使用了 OpenGL::Play() 画了一些基本图形.其中可以尝试去理解一些Api的使用，例如：
    glPushMatrix和glPopMatrix的成对出现：
    glBegin和glEnd的作用：
    glTranslatef： 坐标平移，可以理解为将我们的画笔平移后再作画。
    glRotatef： 坐标旋转，同平移一样,也可以理解为将画笔做一定旋转后再作画。
    glColor3f： 画笔颜色，glSCalef为缩放。
    注意: glaux辅助库..因为比较老的库(我是查网上才这么说的)， 所以不做深究了。