#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#ifndef PLATFORM_WEB
#define FONT_PATH "asset/fonts/iosevka-regular.ttf"
#include <style_dark.h>
#endif

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "raylib + raygui Example");
#ifndef PLATFORM_WEB
    GuiLoadStyleDefault();
    GuiLoadStyleDark();
    Font customFont = LoadFontEx(FONT_PATH, 50, 0, 250);
    GuiSetFont(customFont);
#endif
    SetTargetFPS(60);

    int listScrollIndex = 0;
    int listActive = 0;

    Color pickedColor = SKYBLUE;

    int dropdownActive = 0;
    bool dropdownEditMode = false;

    bool showMessageBox = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        GuiGrid((Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight }, NULL, 20.0f, 2, NULL);

        GuiGroupBox((Rectangle){ 20, 20, 220, 260 }, "GuiListView");
        GuiListView((Rectangle){ 35, 40, 190, 220 },
                    "Item 01;Item 02;Item 03;Item 04;Item 05;Item 06;Item 07;Item 08;Item 09",
                    &listScrollIndex, &listActive);

        GuiGroupBox((Rectangle){ 260, 20, 240, 260 }, "GuiColorPicker");
        GuiColorPicker((Rectangle){ 275, 40, 180, 180 }, NULL, &pickedColor);
        DrawRectangle(275, 230, 205, 35, pickedColor);

        GuiGroupBox((Rectangle){ 520, 20, 250, 120 }, "GuiDropdownBox");
        if (GuiDropdownBox((Rectangle){ 535, 45, 220, 30 }, "Option A;Option B;Option C", &dropdownActive, dropdownEditMode)) {
            dropdownEditMode = !dropdownEditMode;
        }

        if (GuiButton((Rectangle){ 535, 160, 220, 35 }, "Open Message Box")) {
            showMessageBox = true;
        }

        int pass;
        if (showMessageBox) {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RAYWHITE, 0.7f));
            int result = GuiMessageBox((Rectangle){ screenWidth / 2.0f - 150, screenHeight / 2.0f - 75, 300, 150 },
                                       "#191#Modal Dialog", "This is an advance GuiMessageBox!", "OK;Cancel", &pass);

            if (result >= 0) {
                showMessageBox = false;
            }
        }

        GuiStatusBar((Rectangle){ 0, (float)screenHeight - 24, (float)screenWidth, 24 },
                     TextFormat("Selected List Index: %d | Dropdown: %d", listActive, dropdownActive));

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
