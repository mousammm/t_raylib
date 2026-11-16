# raylib (native + wasm) template for x86_64 linux

**EMSDK**

```
$ git clone https://github.com/emscripten-core/emsdk.git
$ cd emsdk
$ ./emsdk install latest
$ ./emsdk activate latest
$ source ./emsdk_env.sh     # need do every time in new shell
```

**SRC_TREE**

```
include
    raygui.h
    raylib.h
lib
    libraylib.a
    libraylib.so
    libraylib.web.a
main.c
Makefile

README.md

index.html
index.js
index.wasm
shell-file.html
```

**CONTROLS**

```
CONTROLS PROVIDED:
  # Container/separators Controls
    - WindowBox     --> StatusBar, Panel
    - GroupBox      --> Line
    - Line
    - Panel         --> StatusBar
    - ScrollPanel   --> StatusBar
    - TabBar        --> Toggle, Button

  # Basic Controls
    - Label
    - LabelButton   --> Label
    - Button
    - Toggle
    - ToggleGroup   --> Toggle
    - ToggleSlider
    - CheckBox
    - ComboBox
    - DropdownBox
    - TextBox
    - ValueBox      --> TextBox
    - Spinner       --> Button, ValueBox
    - Slider
    - SliderBar     --> Slider
    - ProgressBar
    - StatusBar
    - DummyRec
    - Grid

  # Advance Controls
    - ListView
    - ColorPicker   --> ColorPanel, ColorBarHue
    - MessageBox    --> Window, Label, Button
    - TextInputBox  --> Window, Label, TextBox, Button
```
