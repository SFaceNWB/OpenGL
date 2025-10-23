# OpenGL
## P4顶点缓冲区和绘制三角形  
**Vertex Buffer**即缓存区，一块用来存字节的内存，存在与GPU显存(Video RAM)上。C++代码运行在CPU上。  
**OpenGL**可看作一个状态机，与上下文相关，使用它需要选择或绑定所有东西。  
## P5OpenGL中的顶点属性和布局
**Vertex**指的不仅仅是顶点位置，同时包括纹理、法线、颜色、切线这些数据块。  
## P6OpenGL中的着色器工作原理
**Shader**主要使用Vertex Shader和Fragment Shader(Pixel Shader),还有很多其他Shader。
## P18OpenGL中的混合
有src和dest两种颜色，采用RGBA。  
R = (R(src) * A(src)) + (R(dest) * (A(dest) - (1 - A(src)))  
G = (G(src) * A(src)) + (G(dest) * (A(dest) - (1 - A(src)))     
B = (B(src) * A(src)) + (B(dest) * (A(dest) - (1 - A(src)))     
A = (A(src) * A(src)) + (A(dest) * (A(dest) - (1 - A(src)))      