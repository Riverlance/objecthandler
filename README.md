
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
    <td><p align="center"><b>Ctrl</b> + Hold <u>Left</u> Button + [<i><u>Move</u></i>]</p></td>
    <td><p align="center"><u>Increase/Decrease</u> camera <u>zoom</u></p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + Hold <u>Left</u> Button + [<i><u>Move</u></i>]</p></td>
    <td><p align="center"><u>Move</u> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">Hold <u>Left</u> Button + [<i><u>Move</u></i>]</p></td>
    <td><p align="center"><u>Rotate</u> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">Hold <u>Middle</u> Button + [<i><u>Move</u></i>]</p></td>
    <td><p align="center"><u>Move</u> camera</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + Hold <u>Right</u> Button + [<i><u>Move</u></i>]</p></td>
    <td><p align="center"><u>Increase/Decrease</u> camera <u>zoom</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>Wheel</u> Slide</i>]</p></td>
    <td><p align="center"><u>Increase/Decrease</u> camera <u>zoom</u></p></td>
  </tr>
  <tr>
    <td rowspan="42"><p align="center"><b><i>Keyboard</i></b></p></td>
    <td><p align="center"><b>Ctrl</b> + [<i><u>Arrow</u></i>]</p></td>
    <td><p align="center"><u>Increase/Decrease</u> camera <u>zoom</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + [<i><u>Arrow</u></i>]</p></td>
    <td><p align="center"><u>Move</u> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>Arrow</u></i>]</p></td>
    <td><p align="center"><u>Rotate</u> camera</p></td>
  </tr>
  <tr>
    <td><p align="center"><u>W</u> | <u>A</u> | <u>S</u> | <u>D</u></p></td>
    <td><p align="center"><u>Move</u> camera</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>K</u></p></td>
    <td><p align="center"><u>Next camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>M</u></p></td>
    <td><p align="center"><u>Next view mode</u></p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>T</u></p></td>
    <td><p align="center"><u>Next</u> application <u>theme</u></p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <u>1</u></p></td>
    <td><p align="center"><u>Increase mouse</u> camera <u>move</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <u>2</u></p></td>
    <td><p align="center"><u>Increase mouse</u> camera <u>rotate</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <u>3</u></p></td>
    <td><p align="center"><u>Increase mouse</u> camera <u>zoom</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <u>4</u></p></td>
    <td><p align="center"><u>Increase keyboard</u> camera <u>move</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <u>5</u></p></td>
    <td><p align="center"><u>Increase keyboard</u> camera <u>rotate</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <u>6</u></p></td>
    <td><p align="center"><u>Increase keyboard</u> camera <u>zoom</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <u>7</u></p></td>
    <td><p align="center"><u>Increase joystick</u> camera <u>move</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <u>8</u></p></td>
    <td><p align="center"><u>Increase joystick</u> camera <u>rotate</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Shift</b> + <u>9</u></p></td>
    <td><p align="center"><u>Increase joystick</u> camera <u>zoom</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <u>1</u></p></td>
    <td><p align="center"><u>Decrease mouse</u> camera <u>move</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <u>2</u></p></td>
    <td><p align="center"><u>Decrease mouse</u> camera <u>rotate</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <u>3</u></p></td>
    <td><p align="center"><u>Decrease mouse</u> camera <u>zoom</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <u>4</u></p></td>
    <td><p align="center"><u>Decrease keyboard</u> camera <u>move</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <u>5</u></p></td>
    <td><p align="center"><u>Decrease keyboard</u> camera <u>rotate</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <u>6</u></p></td>
    <td><p align="center"><u>Decrease keyboard</u> camera <u>zoom</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <u>7</u></p></td>
    <td><p align="center"><u>Decrease joystick</u> camera <u>move</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <u>8</u></p></td>
    <td><p align="center"><u>Decrease joystick</u> camera <u>rotate</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Alt</b> + <u>9</u></p></td>
    <td><p align="center"><u>Decrease joystick</u> camera <u>zoom</u> sensitivity</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>1</u></p></td>
    <td><p align="center"><u>Reset mouse</u> camera <u>move</u> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>2</u></p></td>
    <td><p align="center"><u>Reset mouse</u> camera <u>rotate</u> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>3</u></p></td>
    <td><p align="center"><u>Reset mouse</u> camera <u>zoom</u> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>4</u></p></td>
    <td><p align="center"><u>Reset keyboard</u> camera <u>move</u> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>5</u></p></td>
    <td><p align="center"><u>Reset keyboard</u> camera <u>rotate</u> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>6</u></p></td>
    <td><p align="center"><u>Reset keyboard</u> camera <u>zoom</u> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>7</u></p></td>
    <td><p align="center"><u>Reset joystick</u> camera <u>move</u> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>8</u></p></td>
    <td><p align="center"><u>Reset joystick</u> camera <u>rotate</u> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center"><b>Ctrl</b> + <u>9</u></p></td>
    <td><p align="center"><u>Reset joystick</u> camera <u>zoom</u> sensitivity to default value</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad <u>Num 8</u></i>]</p></td>
    <td><p align="center">Set to <u>front camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad <u>Num 4</u></i>]</p></td>
    <td><p align="center">Set to <u>right camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad <u>Num 2</u></i>]</p></td>
    <td><p align="center">Set to <u>back camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad <u>Num 6</u></i>]</p></td>
    <td><p align="center">Set to <u>left camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad - (<u>minus</u>)</i>]</p></td>
    <td><p align="center">Set to <u>bottom camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad + (<u>plus</u>)</i>]</p></td>
    <td><p align="center">Set to <u>top camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad / (<u>divide</u>)</i>]</p></td>
    <td><p align="center">Set to <u>diagonal camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i>Keypad * (<u>multiply</u>)</i>]</p></td>
    <td><p align="center"><u>Next camera</u></p></td>
  </tr>
  <tr>
    <td rowspan="13"><p align="center"><b><i>Joystick</i></b><br>(<i>Sony Wireless<br>Joystick Dualshock 4<br>Model CUH-ZCT2U</i>)</p></td>
    <td><p align="center">[<i>Cross <u>Direction</u></i>]</p></td>
    <td><p align="center"><u>Move</u> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>Ball 1</u> Slide</i>]</p></td>
    <td><p align="center"><u>Move</u> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>Ball 2</u> Slide</i>]</p></td>
    <td><p align="center"><u>Rotate</u> camera</p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>X</u> Button</i>]</p></td>
    <td><p align="center">Set to <u>back camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>O</u> Button</i>]</p></td>
    <td><p align="center">Set to <u>left camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>Square</u> Button</i>]</p></td>
    <td><p align="center">Set to <u>right camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>Triangle</u> Button</i>]</p></td>
    <td><p align="center">Set to <u>front camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>L1</u> Button</i>]</p></td>
    <td><p align="center">Set to <u>top camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>R1</u> Button</i>]</p></td>
    <td><p align="center">Set to <u>bottom camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>L2</u> Button</i>]</p></td>
    <td><p align="center"><u>Decrease</u> camera <u>zoom</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>R2</u> Button</i>]</p></td>
    <td><p align="center"><u>Increase</u> camera <u>zoom</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>Start</u></i>]</p></td>
    <td><p align="center"><u>Next camera</u></p></td>
  </tr>
  <tr>
    <td><p align="center">[<i><u>Select</u></i>]</p></td>
    <td><p align="center">Set to <u>diagonal camera</u></p></td>
  </tr>
</table>
<br>

---

### Showoff

TODO

---

### To update

- Grid
