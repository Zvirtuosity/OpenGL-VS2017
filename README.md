# OpenGL-VS2017
 较为详细的**注释**会跟随代码。
 
## 3DFrame_01
 OpenGL框架，直接可以可运行。  
 
    glViewport(0， 0， Width， Height); // 设置OpenGL视口大小。
    glMatrixMode(GL_PROJECTION); // 设置当前矩阵为投影矩阵。
 
## OpenGL的基本图形_02
 这一部分内容使用了 OpenGL::Play() 画了一些基本图形.其中可以尝试去理解一些Api的使用，例如：
 
+ glPushMatrix和glPopMatrix的成对出现：记住当前状态(glTranslatef的值,当再次移动画笔的时候,会基于这个位置做移动)
+ glBegin和glEnd的作用：画笔类型
+ glTranslatef： 坐标平移，可以理解为将我们的画笔平移后再作画。
+ glRotatef： 坐标旋转，同平移一样,也可以理解为将画笔做一定旋转后再作画。
+ glColor3f： 画笔颜色，glSCalef为缩放。

>注意: glaux辅助库..因为比较老的库(我是查网上才这么说的)， 所以不做深究了。  

##  OpenGL的组合图形_03
    glEnable(GL_TEXTURE_2D); // 启用纹理
    glBindTexture(GL_TEXTURE_2D, gPtextureId[1]); //绑定纹理
    gluSphere(gTexture, 0.4f, 8, 8); // 画飞机的头部,球