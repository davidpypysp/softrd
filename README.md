# SoftRd

Welcome to SoftRd, a Software 3D Rendering Engine based on C++.  


This is my individual project due to my interest in computer graphic and rendering pipeline implementation. I developed this project by native C++ from the scratch and refer to OpenGL rendering pipeline standard from [OpenGL Wiki](https://www.khronos.org/opengl/wiki/Rendering_Pipeline_Overview).  

Basically, the renderer is running on GUI based on SDL2.0 and it can load standard model files and render them into scenes by different mode and support basic lighting and different customizing shading effect.  

Now I'm still building the windows version on visual studio, extending new features, optimizing structure and performance. Ideally, it can also support cross platform running on Mac.

## Features

* 3D engine with OpenGL style rendering pipline implementation including vertex shader, primitive assembly,  rasterizing, fragment shader, per-sample operations.
* Support rendering standard .obj file 3D model.
* Support loading texture from popular image format such as .jpg, .png.
* Renderer can render model or mesh in triangle or wireframe mode.
* Support lighting based on Phong lighting model. User can set up different light types(directional light,   spot light, point light) in the scene
* Use GUI to output real-time rendering frames. Support keyboard control and interaction with different objects(models, lights, camera...) in the scene.

## Implementation Details

### Rendering Pipeline Implementation
For this project, basically, I primarily use native C++ 11 to build the total framework of all the rendering pipeline. It could be devided into the following C++ header files which in charges of each stage of the pipeline according to the [OpenGL Rendering Pipeline](https://www.khronos.org/opengl/wiki/Rendering_Pipeline_Overview)
<div align=center>  

![Opengl Rendering Pipeline](https://raw.githubusercontent.com/davidpypysp/softrd/master/files/RenderingPipeline.png)
</div>

```
Rendering pipeline corresponding c++ header file: 

    renderer.h    // control the main loop of renderer program
    |----vertex_shader.h    // vertex shader stage
    |----primitive_assembly.h // vertex post processing and primitive assembly stage
    |----rasterizer.h    // rasteration stage
    |----fragment_shader.h    // fragment shader stage
    |----per_sample_proccessing.h    // per-sample operations stage
```
### Auxiliary Libraries

* SDL2.0 -- For renderer's cross-platform GUI and keyboard I/O.
* Assimp -- Import .obj model into self-defined `model` class object.
* SOIL -- Import diffrent format of image file into `texture` class object.

### Effects

* Single light source with object


## How to install

* TBC

## Test Environment

* Surface Pro4 m3 4GB
* Windows 10
* Visual Studio 2015

## Reference

* [OpenGL Wiki](https://www.khronos.org/opengl/wiki/Rendering_Pipeline_Overview) 
* [Learn OpenGL](https://learnopengl.com/)
* [http://www.songho.ca/opengl/](http://www.songho.ca/opengl/)
* [如何开始用 C++ 写一个光栅化渲染器？](https://www.zhihu.com/question/24786878)




