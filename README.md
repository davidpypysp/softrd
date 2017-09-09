# SoftRd

Welcome to SoftRd, a Software 3D Rendering Engine based on C++.  


This is my individual project due to my interest in computer graphic and rendering pipeline implementation. I developed this project by native C++ from the scratch and refer to OpenGL rendering pipeline standard from [OpenGL Wiki](https://www.khronos.org/opengl/wiki/Rendering_Pipeline_Overview).  

Basically, the renderer is running on GUI based on SDL2.0 and it can load standard model files and render them into scenes by different mode and support basic lighting and different customizing shading effect.  

Now I'm still building the windows version on visual studio, extending new features, optimizing structure and performance. Ideally, it can also support cross platform running on Mac.

## Feature

* 3D engine with OpenGL style rendering pipline implementation including vertex shader, primitive assembly,  rasterizing, fragment shader, per-sample operations.
* Support rendering standard .obj file 3D model.
* Support loading texture from popular image format like .jpg, .png.
* Renderer can render model or mesh in triangle or wireframe mode.
* Support lighting based on Phong lighting model. User can set up different light types(directional light,   spot light, point light) in the scene
* Using GUI output real-time rendering frames. Support keyboard control and interaction with different objects(models, lights, camera...) in the scene.




