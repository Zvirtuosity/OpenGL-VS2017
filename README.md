# OpenGL-VS2017
 较为详细的**注释**会跟随代码。
 
## 1. 3DFrame
 OpenGL框架，直接可以可运行。  
 
    glViewport(0， 0， Width， Height); // 设置OpenGL视口大小。
    glMatrixMode(GL_PROJECTION); // 设置当前矩阵为投影矩阵。
 
## 2. OpenGL的基本图形
 这一部分内容使用了 OpenGL::Play() 画了一些基本图形.其中可以尝试去理解一些Api的使用，例如：
 
+ glPushMatrix和glPopMatrix的成对出现：记住当前状态(glTranslatef的值,当再次移动画笔的时候,会基于这个位置做移动)
+ glBegin和glEnd的作用：画笔类型
+ glTranslatef： 坐标平移，可以理解为将我们的画笔平移后再作画。
+ glRotatef： 坐标旋转，同平移一样,也可以理解为将画笔做一定旋转后再作画。
+ glColor3f： 画笔颜色，glSCalef为缩放。

>注意: glaux辅助库..因为比较老的库(我是查网上才这么说的)， 所以不做深究了。  

##  3. OpenGL的组合图形_03  

    glEnable(GL_TEXTURE_2D); // 启用纹理  
    glBindTexture(GL_TEXTURE_2D, gPtextureId[1]); //绑定纹理
    gluSphere(gTexture, 0.4f, 8, 8); // 画飞机的头部,球
    
## 4. OpenGL摄像机漫游_04  
    void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
                         GLdouble centerx, GLdouble centery, GLdouble centerz,
                         GLdouble upx, GLdouble upy, GLdouble upz);
                         
该函数定义一个视图矩阵，并与当前矩阵相乘。
+ eyex, eyey,eyez 相机在世界坐标的位置
+ centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
+ upx,upy,upz 相机向上的方向在世界坐标中的方向  

你把相机想象成为你自己的脑袋：

+ eyex, eyey,eyez脑袋的位置
+ centerx,centery,centerz 眼睛看的物体的位置
+ upx,upy,upz头顶朝向的方向（因为你可以歪着头看同一个物体）
> 参考:[OpenGL的gluLookAt观察变换函数详解](http://www.cnblogs.com/1024Planet/p/5641283.html)
