/*
*   CONTROLS PROVIDED:
*     # Container/separators Controls
*       - WindowBox     --> StatusBar, Panel
*       - GroupBox      --> Line
*       - Line
*       - Panel         --> StatusBar
*       - ScrollPanel   --> StatusBar
*       - TabBar        --> Toggle, Button
*
*     # Basic Controls
*       - Label
*       - LabelButton   --> Label
*       - Button
*       - Toggle
*       - ToggleGroup   --> Toggle
*       - ToggleSlider
*       - CheckBox
*       - ComboBox
*       - DropdownBox
*       - TextBox
*       - ValueBox      --> TextBox
*       - Spinner       --> Button, ValueBox
*       - Slider
*       - SliderBar     --> Slider
*       - ProgressBar
*       - StatusBar
*       - DummyRec
*       - Grid
*
*     # Advance Controls
*       - ListView
*       - ColorPicker   --> ColorPanel, ColorBarHue
*       - MessageBox    --> Window, Label, Button
*       - TextInputBox  --> Window, Label, TextBox, Button
*/

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_DEBUG_RECS_BOUNDS
#define RAYGUI_DEBUG_TEXT_BOUNDS
#include <raygui.h>

#define FONT_PATH "./asset/fonts/iosevka-regular.ttf"
#define GUI_STYLE "./asset/styles/style_dark.rgs"

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raygui - GuiScrollPanel()");
    Font customFont = LoadFontEx(FONT_PATH, 50, 0, 250);
    GuiSetFont(customFont);
    GuiLoadStyle(GUI_STYLE);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTextEx(customFont, "Hello world", (Vector2){100, 40}, customFont.baseSize, 1, RED);
        EndDrawing();
    }
}
