
# Object Handler

**Object Handler** is a 3D model viewer written in C++.

---

### Features

##### Main

* Normal vectors being generated automatically (flag aiProcess_GenNormals)
* Shading with GLSL
* Phong shading
* Supported object files: ASSIMP supported object files (obj, fbx, 3ds, ...)

##### Camera

* Camera rotation: Pitch constraint or Pitch constraint break (default)
* 7 camera positions
* Camera controls: move, rotate, zoom, change camera view

##### Control

* Devices: Mouse, Keyboard, Joystick (including more than one at the same time; e.g., mouse + keyboard, or joystick 1 + joystick 2 + keyboard, ...)
* Smooth sensibility (SDL pollEvents and pumpEvents)
* Sensibility for mouse, keyboard and joystick
* Theme (dark by default, or light)

##### Advanced

* Working with Release x64, Release x86, Debug x64, Debug x86
* Debug opens a console window with util informations for debugging
* Code working with warning level 4

---

### Technologies

* **OpenGL** 3.3 (_GLEW_ 2.0.0)
* **SDL** 2
* **SOIL** 2
* **GLM** 0.9.9.5
* **Assimp** 4.1.0

---

### To update

- _View modes_: _Texture_ (default) / _Flat Shade_ / _Wireframe_
- Options changing in real time: sensibility, theme, camera position, view mode, joystick dead zone, ...
- Show util data like: meshes count, vertices count, mesh faces count, ...
- Grid
