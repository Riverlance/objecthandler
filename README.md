
# Object Handler

**Object Handler** is a 3D model viewer written in C++.

---

### Features

##### Main

* Supported object files: ASSIMP supported object file extensions (obj, fbx, 3ds, ...)
* Modern OpenGL shading (VAO, VBO, EBO, ...)
* Phong shading
* Shading with GLSL
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
    <td><p align="center"><b>Ctrl</b> + Hold <i>Left</i> Button + [<i>Move</i>]</p></td>
    <td><p align="center"><i>Increase/Decrease</i> camera <i>zoom</i></p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + Hold <i>Left</i> Button + [<i>Move</i>]</p></td>
    <td><p align="center"><i>Move</i> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">Hold <i>Left</i> Button + [<i>Move</i>]</p></td>
    <td><p align="center"><i>Rotate</i> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">Hold <i>Middle</i> Button + [<i>Move</i>]</p></td>
    <td><p align="center"><i>Move</i> camera</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + Hold <i>Right</i> Button + [<i>Move</i>]</p></td>
    <td><p align="center"><i>Increase/Decrease</i> camera <i>zoom</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Wheel Slide</i>]</p></td>
    <td><p align="center"><i>Increase/Decrease</i> camera <i>zoom</i></p></td>
  </tr>
  <tr>
    <td rowspan="42"><p align="center"><b><i>Keyboard</i></b></p></td>
    <td><p align="center"><b>Ctrl</b> + [<i>Arrow</i>]</p></td>
    <td><p align="center"><i>Increase/Decrease</i> camera <i>zoom</i></p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + [<i>Arrow</i>]</p></td>
    <td><p align="center"><i>Move</i> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Arrow</i>]</p></td>
    <td><p align="center"><i>Rotate</i> camera</p></td>
  </tr>
  <tr>
    <td><p align="center"><i>W</i> | <i>A</i> | <i>S</i> | <i>D</i></p></td>
    <td><p align="center"><i>Move</i> camera</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>K</i></p></td>
    <td><p align="center"><i>Next camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>M</i></p></td>
    <td><p align="center"><i>Next view mode</i></p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>T</i></p></td>
    <td><p align="center"><i>Next</i> application <i>theme</i></p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <i>1</i></p></td>
    <td><p align="center"><i>Increase mouse</i> camera <i>move</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <i>2</i></p></td>
    <td><p align="center"><i>Increase mouse</i> camera <i>rotate</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <i>3</i></p></td>
    <td><p align="center"><i>Increase mouse</i> camera <i>zoom</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <i>4</i></p></td>
    <td><p align="center"><i>Increase keyboard</i> camera <i>move</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <i>5</i></p></td>
    <td><p align="center"><i>Increase keyboard</i> camera <i>rotate</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <i>6</i></p></td>
    <td><p align="center"><i>Increase keyboard</i> camera <i>zoom</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <i>7</i></p></td>
    <td><p align="center"><i>Increase joystick</i> camera <i>move</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <i>8</i></p></td>
    <td><p align="center"><i>Increase joystick</i> camera <i>rotate</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <i>9</i></p></td>
    <td><p align="center"><i>Increase joystick</i> camera <i>zoom</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <i>1</i></p></td>
    <td><p align="center"><i>Decrease mouse</i> camera <i>move</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <i>2</i></p></td>
    <td><p align="center"><i>Decrease mouse</i> camera <i>rotate</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <i>3</i></p></td>
    <td><p align="center"><i>Decrease mouse</i> camera <i>zoom</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <i>4</i></p></td>
    <td><p align="center"><i>Decrease keyboard</i> camera <i>move</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <i>5</i></p></td>
    <td><p align="center"><i>Decrease keyboard</i> camera <i>rotate</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <i>6</i></p></td>
    <td><p align="center"><i>Decrease keyboard</i> camera <i>zoom</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <i>7</i></p></td>
    <td><p align="center"><i>Decrease joystick</i> camera <i>move</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <i>8</i></p></td>
    <td><p align="center"><i>Decrease joystick</i> camera <i>rotate</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <i>9</i></p></td>
    <td><p align="center"><i>Decrease joystick</i> camera <i>zoom</i> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>1</i></p></td>
    <td><p align="center"><i>Reset mouse</i> camera <i>move</i> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>2</i></p></td>
    <td><p align="center"><i>Reset mouse</i> camera <i>rotate</i> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>3</i></p></td>
    <td><p align="center"><i>Reset mouse</i> camera <i>zoom</i> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>4</i></p></td>
    <td><p align="center"><i>Reset keyboard</i> camera <i>move</i> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>5</i></p></td>
    <td><p align="center"><i>Reset keyboard</i> camera <i>rotate</i> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>6</i></p></td>
    <td><p align="center"><i>Reset keyboard</i> camera <i>zoom</i> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>7</i></p></td>
    <td><p align="center"><i>Reset joystick</i> camera <i>move</i> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>8</i></p></td>
    <td><p align="center"><i>Reset joystick</i> camera <i>rotate</i> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <i>9</i></p></td>
    <td><p align="center"><i>Reset joystick</i> camera <i>zoom</i> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad Num 8</i>]</p></td>
    <td><p align="center">Set to <i>front camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad Num 4</i>]</p></td>
    <td><p align="center">Set to <i>right camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad Num 2</i>]</p></td>
    <td><p align="center">Set to <i>back camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad Num 6</i>]</p></td>
    <td><p align="center">Set to <i>left camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad - (minus)</i>]</p></td>
    <td><p align="center">Set to <i>bottom camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad + (plus)</i>]</p></td>
    <td><p align="center">Set to <i>top camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad / (divide)</i>]</p></td>
    <td><p align="center">Set to <i>diagonal camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad * (multiply)</i>]</p></td>
    <td><p align="center"><i>Next camera</i></p></td>
  </tr>
  <tr>
    <td rowspan="13"><p align="center"><b><i>Joystick</i></b><br>(<i>Sony Wireless<br>Joystick Dualshock 4<br>Model CUH-ZCT2U</i>)</p></td>
    <td><p align="center">[<i>Cross Direction</i>]</p></td>
    <td><p align="center"><i>Move</i> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Ball 1 Slide</i>]</p></td>
    <td><p align="center"><i>Move</i> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Ball 2 Slide</i>]</p></td>
    <td><p align="center"><i>Rotate</i> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>X Button</i>]</p></td>
    <td><p align="center">Set to <i>back camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>O Button</i>]</p></td>
    <td><p align="center">Set to <i>left camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Square Button</i>]</p></td>
    <td><p align="center">Set to <i>right camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Triangle Button</i>]</p></td>
    <td><p align="center">Set to <i>front camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>L1 Button</i>]</p></td>
    <td><p align="center">Set to <i>top camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>R1 Button</i>]</p></td>
    <td><p align="center">Set to <i>bottom camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>L2 Button</i>]</p></td>
    <td><p align="center"><i>Decrease</i> camera <i>zoom</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>R2 Button</i>]</p></td>
    <td><p align="center"><i>Increase</i> camera <i>zoom</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Start</i>]</p></td>
    <td><p align="center"><i>Next camera</i></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Select</i>]</p></td>
    <td><p align="center">Set to <i>diagonal camera</i></p></td>
  </tr>
</table>
<br>

---

### Showoff

TODO

---

### To update

- Grid
