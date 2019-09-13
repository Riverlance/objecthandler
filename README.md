
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

<br>
<table style="width:100%">
  <tr>
    <th><p align="center"><b>Device</b></p></th>
    <th><p align="center"><b>Shortcut</b></p></th>
    <th><p align="center"><b>Action</b></p></th>
  </tr>
  <tr>
    <td rowspan="6"><p align="center"><b><i>Mouse</i></b></p></td>
    <td><p align="center"><b>Ctrl</b> + Hold Left Button + [<i>Move</i>]</p></td>
    <td><p align="center">Increase/Decrease camera zoom</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + Hold Left Button + [<i>Move</i>]</p></td>
    <td><p align="center">Move camera</p></td>
  </tr>
  <tr>
    <td><p align="center">Hold Left Button + [<i>Move</i>]</p></td>
    <td><p align="center">Rotate camera</p></td>
  </tr>
  <tr>
    <td><p align="center">Hold Middle Button + [<i>Move</i>]</p></td>
    <td><p align="center">Move camera</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + Hold Right Button + [<i>Move</i>]</p></td>
    <td><p align="center">Increase/Decrease camera zoom</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Wheel Slide</i>]</p></td>
    <td><p align="center">Increase/Decrease camera zoom</p></td>
  </tr>
  <tr>
    <td rowspan="42"><p align="center"><b><i>Keyboard</i></b></p></td>
    <td><p align="center"><b>Ctrl</b> + [<i>Arrow</i>]</p></td>
    <td><p align="center">Increase/Decrease camera zoom</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + [<i>Arrow</i>]</p></td>
    <td><p align="center">Move camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Arrow</i>]</p></td>
    <td><p align="center">Rotate camera</p></td>
  </tr>
  <tr>
    <td><p align="center">W | A | S | D</p></td>
    <td><p align="center">Move camera</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + K</p></td>
    <td><p align="center">Next camera</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + M</p></td>
    <td><p align="center">Next view mode</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + T</p></td>
    <td><p align="center">Next application theme</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + 1</p></td>
    <td><p align="center">Increase mouse camera move sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + 2</p></td>
    <td><p align="center">Increase mouse camera rotate sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + 3</p></td>
    <td><p align="center">Increase mouse camera zoom sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + 4</p></td>
    <td><p align="center">Increase keyboard camera move sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + 5</p></td>
    <td><p align="center">Increase keyboard camera rotate sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + 6</p></td>
    <td><p align="center">Increase keyboard camera zoom sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + 7</p></td>
    <td><p align="center">Increase joystick camera move sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + 8</p></td>
    <td><p align="center">Increase joystick camera rotate sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + 9</p></td>
    <td><p align="center">Increase joystick camera zoom sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + 1</p></td>
    <td><p align="center">Decrease mouse camera move sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + 2</p></td>
    <td><p align="center">Decrease mouse camera rotate sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + 3</p></td>
    <td><p align="center">Decrease mouse camera zoom sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + 4</p></td>
    <td><p align="center">Decrease keyboard camera move sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + 5</p></td>
    <td><p align="center">Decrease keyboard camera rotate sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + 6</p></td>
    <td><p align="center">Decrease keyboard camera zoom sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + 7</p></td>
    <td><p align="center">Decrease joystick camera move sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + 8</p></td>
    <td><p align="center">Decrease joystick camera rotate sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + 9</p></td>
    <td><p align="center">Decrease joystick camera zoom sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + 1</p></td>
    <td><p align="center">Reset mouse camera move sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + 2</p></td>
    <td><p align="center">Reset mouse camera rotate sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + 3</p></td>
    <td><p align="center">Reset mouse camera zoom sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + 4</p></td>
    <td><p align="center">Reset keyboard camera move sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + 5</p></td>
    <td><p align="center">Reset keyboard camera rotate sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + 6</p></td>
    <td><p align="center">Reset keyboard camera zoom sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + 7</p></td>
    <td><p align="center">Reset joystick camera move sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + 8</p></td>
    <td><p align="center">Reset joystick camera rotate sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + 9</p></td>
    <td><p align="center">Reset joystick camera zoom sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad Num 8</i>]</p></td>
    <td><p align="center">Set to front camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad Num 4</i>]</p></td>
    <td><p align="center">Set to right camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad Num 2</i>]</p></td>
    <td><p align="center">Set to back camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad Num 6</i>]</p></td>
    <td><p align="center">Set to left camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad - (minus)</i>]</p></td>
    <td><p align="center">Set to bottom camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad + (plus)</i>]</p></td>
    <td><p align="center">Set to top camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad / (divide)</i>]</p></td>
    <td><p align="center">Set to diagonal camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad * (multiply)</i>]</p></td>
    <td><p align="center">Next camera</p></td>
  </tr>
  <tr>
    <td rowspan="13"><p align="center"><b><i>Joystick</i></b><br>(<i>Sony Wireless<br>Joystick Dualshock 4<br>Model CUH-ZCT2U</i>)</p></td>
    <td><p align="center">[<i>Cross Direction</i>]</p></td>
    <td><p align="center">Move camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Ball 1 Slide</i>]</p></td>
    <td><p align="center">Move camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Ball 2 Slide</i>]</p></td>
    <td><p align="center">Rotate camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>X Button</i>]</p></td>
    <td><p align="center">Set to back camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>O Button</i>]</p></td>
    <td><p align="center">Set to left camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Square Button</i>]</p></td>
    <td><p align="center">Set to right camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Triangle Button</i>]</p></td>
    <td><p align="center">Set to front camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>L1 Button</i>]</p></td>
    <td><p align="center">Set to top camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>R1 Button</i>]</p></td>
    <td><p align="center">Set to bottom camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>L2 Button</i>]</p></td>
    <td><p align="center">Decrease camera zoom</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>R2 Button</i>]</p></td>
    <td><p align="center">Increase camera zoom</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Start</i>]</p></td>
    <td><p align="center">Next camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Select</i>]</p></td>
    <td><p align="center">Set to diagonal camera</p></td>
  </tr>
</table>
<br>

---

### Showoff

TODO

---

### To update

- Grid
