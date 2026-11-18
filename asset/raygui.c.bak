#include <stdio.h>
// raygui todo: add dynamic rectangle that track the mouse pos and update the rect

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <style_dark.h>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "title");
    GuiLoadStyleDefault();
    GuiLoadStyleDark();
    SetTargetFPS(60);

    int showMsgBox = false;
    bool a_guiToggle = true;
    int a_guiToggleGroup = false;
    int    iInt   = 0;
    float  fFloat = 0.0f;
    bool   bBool  = 0;
    char dText[100] = {0};
    int guiDropDownBoolActive = 1;
    Vector2 mouseCell = { -1, -1 };
    Color color = RED;
    float alpha = 1.0f;
    float hue = 0.0f;
    Vector3 colorHsv = { 0.0f, 1.0f, 1.0f };
    int btnActive = -1;
    char textBuffer[64] = "";
    bool secretView = false;
    char *listItems[] = { "Item 1", "Item 2", "Item 3" };
    int scrollIndex = 0;
    int activeItem = 0;
    int focusItem = -1;


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

#if 1 /* Container/separator(organize controls) */
        GuiWindowBox((Rectangle){20, 20, 200, 150}, "GuiWindowBox");
        GuiPanel((Rectangle){20, 40 + 150, 200, 150}, "GuiPanel");
        GuiScrollPanel((Rectangle){20, 60 + 150*2, 200, 150}, "GuiScrollPanel", (Rectangle){20, 60 + 150*2, 200, 150}, NULL, NULL);
        GuiGroupBox((Rectangle){20, 80 + 150*3, 200, 150}, "GuiGroupBox");
        GuiLine((Rectangle){20, 80 + 150*4, 200, 30}, "GuiLine");
        GuiLine((Rectangle){20, 100 + 150*4, 200, 30}, NULL);
#endif

#if 1 /* BASIC CONTROL Set */
        GuiLabel((Rectangle){300, 20, 100, 20}, "GuiLable");    // just a text
        GuiButton((Rectangle){300, 20+20, 100, 20}, "GuiButton"); // return true on click
        GuiLabelButton((Rectangle){300, 20+20*2, 100, 20}, "GuiLabelButton");  // text return true when click 
        GuiToggle((Rectangle){300, 20+20*3, 100, 20}, "GuiToggle", &a_guiToggle);
        GuiToggleGroup((Rectangle){300, 20+20*4, 100, 20}, "GuiToggleGroup", &a_guiToggleGroup);
        GuiToggleSlider((Rectangle){300, 20+20*5, 100, 20}, "GuiToggleSlider", &a_guiToggleGroup);
        GuiCheckBox((Rectangle){300, 20+20*6, 20, 20}, "GuiCheckBox", &a_guiToggle);
        GuiComboBox((Rectangle){300, 20+20*7, 20, 20}, "a;b;c", &a_guiToggleGroup); 

        GuiDropdownBox((Rectangle){300, 20+20*8, 100, 20}, "Apple;Banana", &guiDropDownBoolActive, false);
        GuiSpinner((Rectangle){300, 20*10, 100, 20}, "GuiSpinner", &iInt, 0, 100, &bBool);
        GuiValueBox((Rectangle){300, 20*11, 100, 20}, "GuiValueBox", &iInt, 0, 100, &bBool);
        GuiValueBoxFloat((Rectangle){300, 20*12, 100, 20}, "GuiValueBoxFloat", NULL, NULL, NULL);
        GuiTextBox((Rectangle){300, 20*13, 100, 20}, dText, 100, &bBool);

        GuiSlider((Rectangle){300, 20*14, 100, 20}, NULL, NULL, NULL, 0, 100); // Slider control
        GuiSliderBar((Rectangle){300, 20*15, 100, 20}, NULL, NULL, NULL, 0, 100); // Slider Bar control
        GuiProgressBar((Rectangle){300, 20*16, 100, 20}, NULL, NULL, NULL, 0, 100); // Progress Bar control
        if (a_guiToggle) { GuiStatusBar((Rectangle){0,screenHeight-30,screenWidth, 30}, "GuiStatusBar"); }
        GuiDummyRec((Rectangle){300, 20*17, 100, 20}, "GuiDummyRec");
        GuiGrid((Rectangle){ 300, 20*18, 100, 100 }, NULL, 5.0f, 1, &mouseCell);
#endif

#if 1 /* Advanced Control */
        GuiMessageBox((Rectangle){ 300, 20*19+100, 250, 100 }, "Title", "Message here", "OK;Cancel", &btnActive);
        GuiTextInputBox((Rectangle){ 300, 20*20+100*2, 250, 140 }, "Input", "Enter text:", textBuffer, 64, "Save;Cancel", &btnActive, &secretView);
        GuiListViewEx((Rectangle){ 430, 20, 120, 100 }, listItems, 3, &scrollIndex, &activeItem, &focusItem);
        GuiListView((Rectangle){ 430, 20+100, 120, 100 }, "a;b;c", &scrollIndex, &activeItem);
#endif

#if 1 /* color control */
        GuiColorPicker((Rectangle){ 600, 20*1, 150, 150 }, NULL, &color);
        GuiColorPanel((Rectangle){ 600, 20*2+150, 150, 150 }, NULL, &color);
        GuiColorBarAlpha((Rectangle){ 600, 20*3+150*2, 150, 20 }, NULL, &alpha);
        GuiColorBarHue((Rectangle){ 560, 20*2+150, 20, 150 }, NULL, &hue);
        GuiColorPickerHSV((Rectangle){ 600, 20*5+150*2, 150, 150 }, NULL, &colorHsv);
        GuiColorPanelHSV((Rectangle){ 600, 20*6+150*3, 150, 150 }, NULL, &colorHsv);
#endif

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
