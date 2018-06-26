# OpenGL参考页面的API[参考链接](https://www.khronos.org/registry/OpenGL-Refpages/es3/)  
  - abs 求绝对值
  - acos 求反三角函数cos
  - acosh 求反弧双曲余弦cosh?不懂公式
  - glActiveShaderProgram 设置,定义编程管线到一个程序物体.3.1后才有的API.不知道拿来做什么
  - glActiveTexture 选中活动纹理单元, 激活GLenum texture纹理单元.激活之后可以做什么?
  - all 检查布尔类型的矩阵,是否全部为true
  - any 检查布尔类型的矩阵, 是否有一个为true
  - asin 略
  - asinh 略
  - atan 略
  - atanh 略3.10
  - atomicAdd 3.10才支持
  - atomicAnd 3.10才支持
  - atomicCompSwap  3.10才支持
  - atomicCounter 3.10才支持
  - atomicCounterDecrement 3.10才支持
  - atomicCounterIncrement 3.10才支持
  - atomicExchange 3.10才支持
  - atomicMax 3.10才支持
  - atomicMin 3.10才支持
  - atomicOr 3.10才支持
  - atomicXor 3.10才支持
  - glAttachShader 附加一段shader程序到program object
    被Linked到prgram object的Shader, 必须先被AttachShader.这意味着shader在Program将要执行的链接操作中被包含进来.
    所有合法的shader对象都被被运行起来, 无论是否被附加到program object, 才源码加载之前或者Shader再编译之前, 是可以Attached一段Shader object.
    不允许Attached同一类的Shader被附加多次.允许一个物体Attached超过一个Shader,当Shader被Attached到program时删除Shader,此时不会删除而是标记为删除,一直等到glDetachShader将Shader从detach才会删除
> 3.10才支持的暂时不做了解, 因为多半用不到
  - barrier 3.10才支持
  - glBeginQuery 作用:开始一次遮挡查询为每个所需的遮挡查询生成一个查询ID；1.调用glBeginQuery()，表示开始一个遮挡查询； 2.渲染需要进行遮挡查询的几何图形； 3.调用glEndQuery()，表示已经完成了遮挡查询； 4.提取通过了遮挡查询的样本数量。
[查询帧缓冲区的用法](http://codercdy.com/2015/06/11/openglxue-xi-bi-ji-zheng-huan-chong-qu/),[镇缓冲区效果](https://blog.csdn.net/wangdingqiaoit/article/details/52423060):镜面，离屏渲染，以及很酷的后处理效果,块传输bilt是一个很重要的技术, 未完待续,官方解释没完全理解
  - glBeginTransformFeedback
  - glBindAttribLocation
  - glBindBuffer
  - glBindBufferBase
  - glBindBufferRange
  - glBindFramebuffer
  - glBindImageTexture
  - glBindProgramPipeline
  - glBindRenderbuffer
  - glBindSampler
  - glBindTexture
  - glBindTransformFeedback
  - glBindVertexArray
  - glBindVertexBuffer
  - bitCount
  - bitfieldExtract
  - bitfieldInsert
  - bitfieldReverse
  - glBlendBarrier
  - glBlendColor
  - glBlendEquation
  - glBlendEquationi
  - glBlendEquationSeparate
  - glBlendEquationSeparatei
  - glBlendFunc
  - glBlendFunci
  - glBlendFuncSeparate
  - glBlendFuncSeparatei
  - glBlitFramebuffer
  - glBufferData
  - glBufferSubData



  > 因为较多, 不能一一整理现在.暂时摘录了如下内容:
## 内置函数库
glsl提供了非常丰富的函数库,供我们使用,这些功能都是非常有用且会经常用到的. 这些函数按功能区分大改可以分成7类:

#### 通用函数:
下文中的类型T可以是float, vec2, vec3, vec4,且可以逐分量操作.
方法   说明
```
T abs(T x)  返回x的绝对值
T sign(T x)  比较x与0的值,大于,等于,小于分别返回1.0 ,0.0,-1.0
T floor(T x)  返回<=x的最大整数
T ceil(T x)  返回>=等于x的最小整数
T fract(T x)  获取x的小数部分
T mod(T x, T y) 
T mod(T x, float y)  取x,y的余数
T min(T x, T y) 
T min(T x, float y)  取x,y的最小值
T max(T x, T y) 
T max(T x, float y)  取x,y的最大值
T clamp(T x, T minVal, T maxVal) 
T clamp(T x, float minVal,float maxVal)  min(max(x, minVal), maxVal),返回值被限定在minVal,maxVal之间
T mix(T x, T y, T a) 
T mix(T x, T y, float a)  取x,y的线性混合,x*(1-a)+y*a
T step(T edge, T x) 
T step(float edge, T x)  如果x<edge 返回0.0 否则返回1.0
T smoothstep(T edge0, T edge1, T x) 
T smoothstep(float edge0,float edge1, T x)  如果x<edge0 返回0.0 如果x>edge1返回1.0, 否则返回Hermite插值
```

#### 角度&三角函数:
下文中的类型T可以是float, vec2, vec3, vec4,且可以逐分量操作.
方法   说明
```
T radians(T degrees)  角度转弧度
T degrees(T radians)  弧度转角度
T sin(T angle)  正弦函数,角度是弧度
T cos(T angle)  余弦函数,角度是弧度
T tan(T angle)  正切函数,角度是弧度
T asin(T x)  反正弦函数,返回值是弧度
T acos(T x)  反余弦函数,返回值是弧度
T atan(T y, T x) 
T atan(T y_over_x)  反正切函数,返回值是弧度
```

#### 指数函数:
下文中的类型T可以是float, vec2, vec3, vec4,且可以逐分量操作.
方法   说明
```
T pow(T x, T y)  返回x的y次幂x y
T exp(T x)  返回x的自然指数幂e x
T log(T x)  返回x的自然对数ln
T exp2(T x)  返回2的x次幂2 x
T log2(T x)  返回2为底的对数log2
T sqrt(T x)  开根号√x
T inversesqrt(T x)  先开根号,在取倒数,就是1/√x
```

#### 几何函数:
下文中的类型T可以是float, vec2, vec3, vec4,且可以逐分量操作.
方法   说明
```
float length(T x) 返回矢量x的长度
float distance(T p0, T p1) 返回p0 p1两点的距离
float dot(T x, T y) 返回xy的点积
vec3 cross(vec3 x, vec3 y) 返回xy的叉积
T normalize(T x) 对x进行归一化,保持向量方向不变但长度变为1
T faceforward(TN, TI, T Nref) 根据矢量N 与Nref 调整法向量
T reflect(TI, TN) 返回I - 2 * dot(N,I) * N, 结果是入射矢量I 关于法向量N的镜面反射矢量
T refract(TI, TN, float eta) 返回入射矢量I关于法向量N的折射矢量,折射率为eta
```

#### 矩阵函数:
mat可以为任意类型矩阵.
方法   说明
```
mat matrixCompMult(mat x, mat y)
将矩阵x 和y的元素逐分量相乘
```
#### 向量函数:
下文中的类型T可以是vec2, vec3, vec4, 且可以逐分量操作.

bvec指的是由bool类型组成的一个向量:
```
vec3 v3= vec3(0 .,0 .,0 .);
vec3 v3_1= vec3(1 .,1 .,1 .);
bvec3 aa= lessThan(v3,v3_1);// bvec3(true,true,true)
bvec lessThan(T x, T y) 逐分量比较x < y,将结果写入bvec对应位置
bvec lessThanEqual(T x, T y)  逐分量比较x <= y,将结果写入bvec对应位置
bvec greaterThan(T x, T y)  逐分量比较x > y,将结果写入bvec对应位置
bvec greaterThanEqual(T x, T y)  逐分量比较x >= y,将结果写入bvec对应位置
bvec equal(T x, T y) 
bvec equal(bvec x, bvec y)  逐分量比较x == y,将结果写入bvec对应位置
bvec notEqual(T x, T y) 
bvec notEqual(bvec x, bvec y)  逐分量比较x!= y,将结果写入bvec对应位置
bool any(bvec x)  如果x的任意一个分量是true,则结果为true
bool all(bvec x)  如果x的所有分量是true,则结果为true
bvec not(bvec x) bool矢量的逐分量取反
```
#### 纹理查询函数:
图像纹理有两种一种是平面2d纹理,另一种是盒纹理,针对不同的纹理类型有不同访问方法.
纹理查询的最终目的是从sampler中提取指定坐标的颜色信息. 函数中带有Cube字样的是指需要传入盒状纹理. 带有Proj字样的是指带投影的版本.
以下函数只在vertex shader中可用:
```
vec4 texture2DLod (sampler2D sampler, vec2 coord,float lod);
vec4 texture2DProjLod (sampler2D sampler, vec3 coord,float lod);
vec4 texture2DProjLod (sampler2D sampler, vec4 coord,float lod);
vec4 textureCubeLod (samplerCube sampler, vec3 coord,float lod);
以下函数只在fragment shader中可用:
vec4 texture2D (sampler2D sampler, vec2 coord,float bias);
vec4 texture2DProj (sampler2D sampler, vec3 coord,float bias);
vec4 texture2DProj (sampler2D sampler, vec4 coord,float bias);
vec4 textureCube (samplerCube sampler, vec3 coord,float bias);
在vertex shader 与fragment shader 中都可用:
vec4 texture2D (sampler2D sampler, vec2 coord);
vec4 texture2DProj (sampler2D sampler, vec3 coord);
vec4 texture2DProj (sampler2D sampler, vec4 coord);
vec4 textureCube (samplerCube sampler, vec3 coord);
```
#### 官方的shader范例:
下面的shader如果你可以一眼看懂,说明你已经对glsl语言基本掌握了.
```
Vertex Shader:
uniform mat4 mvp_matrix;//透视矩阵*视图矩阵*模型变换矩阵 
uniform mat3 normal_matrix;//法线变换矩阵(用于物体变换后法线跟着变换) 
uniform vec3 ec_light_dir;//光照方向 
attribute vec4 a_vertex;//顶点坐标 
attribute vec3 a_normal;//顶点法线 
attribute vec2 a_texcoord;//纹理坐标 
varying float v_diffuse;//法线与入射光的夹角 
varying vec2 v_texcoord;// 2d纹理坐标void main (void )
{
 //归一化法线 
 vec3 ec_normal = normalize (normal_matrix * a_normal);
  // v_diffuse是法线与光照的夹角.根据向量点乘法则,当两向量长度为1是乘积即cosθ值 
 v_diffuse = max ( dot (ec_light_dir, ec_normal), 0.0 );
 v_texcoord = a_texcoord;
 gl_Position = mvp_matrix * a_vertex;
}

Fragment Shader:
precision mediumpfloat ;
uniform sampler2D t_reflectance;
uniform vec4 i_ambient;
varying float v_diffuse;
varying vec2 v_texcoord;void main (void )
{
 vec4 color =texture2D (t_reflectance, v_texcoord);
  //这里分解开来是color*vec3(1,1,1)*v_diffuse + color*i_ambient
 //色*光*夹角cos +色*环境光 
 gl_FragColor = color*(vec4 (v_diffuse) + i_ambient);

}
```
