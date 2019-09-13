
# Object Handler

**Object Handler** is a 3D model viewer written in C++.

---

### Features

##### Main

* Supported object files: ASSIMP supported object file extensions (obj, fbx, 3ds, ...)
* Shading with GLSL
* Phong shading
* Normal vectors being generated automatically (flag aiProcess_GenNormals)
* All polygons as triangles (flag aiProcess_Triangulate)

##### Camera

* Camera rotation: Pitch constraint or Pitch constraint break (default)
* 7 camera positions: front, right, back, left, top, bottom, diagonal
* Camera controls: move, rotate, zoom, change camera view

##### Control

* Devices: Mouse, Keyboard, Joystick (including more than one at the same time; e.g., mouse + keyboard, or joystick 1 + joystick 2 + keyboard, ...)
* Smooth sensibility (SDL pollEvents and pumpEvents)
* Sensibility for mouse, keyboard and joystick
* View modes: fill (textured) by default, line (wireframe) or point (vertices)
* Themes: dark by default or light

##### Advanced

* Working with Release x64, Release x86, Debug x64, Debug x86
* Debug opens a console window with util informations for debugging, including meshes/triangles/vertices count, action logs, and so on
* Code working with warning level 4

---

### Technologies

* **OpenGL** 3.3 (_GLEW_ 2.0.0)
* **SDL** 2
* **SOIL** 2
* **GLM** 0.9.9.5
* **Assimp** 4.1.0

---

### Shortcuts

TODO

---

### Showoff

TODO

---

### To update

- Grid
