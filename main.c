#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION
        
#include <raymath.h>
#include <rlgl.h>
#include <style_dark.h>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Raylib wasm demo!");
    GuiLoadStyleDefault();
    GuiLoadStyleDark();

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 3.0f, 6.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 rotation = { 0.0f, 0.0f, 0.0f };
    float prevPinchDist = 0.0f;

    Rectangle panelBounds = { 15, 15, 210, 250 };
    bool showWindow = true;
    bool autoSpin = true;
    Color bgColor = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        Vector2 pointerPos = GetMousePosition();
        bool isOverUI = showWindow && CheckCollisionPointRec(pointerPos, panelBounds);

        if (autoSpin) {
            rotation.x += 45.0f * dt;
            rotation.y += 60.0f * dt;
            rotation.z += 30.0f * dt;
        }

        if (!isOverUI && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetTouchPointCount() <= 1) {
            Vector2 delta = GetMouseDelta();
            rotation.y += delta.x * 0.5f;
            rotation.x += delta.y * 0.5f;
        }

        float wheel = GetMouseWheelMove();
        if (!isOverUI && wheel != 0) {
            camera.position.z -= wheel * 0.5f;
        }

        if (GetTouchPointCount() == 2) {
            Vector2 t0 = GetTouchPosition(0);
            Vector2 t1 = GetTouchPosition(1);
            float currDist = Vector2Distance(t0, t1);

            if (prevPinchDist > 0.0f) {
                camera.position.z -= (currDist - prevPinchDist) * 0.02f;
            }
            prevPinchDist = currDist;
        } else {
            prevPinchDist = 0.0f;
        }

        if (camera.position.z < 2.0f) camera.position.z = 2.0f;

        BeginDrawing();
            ClearBackground(bgColor);

            BeginMode3D(camera);
                DrawGrid(10, 1.0f);

                rlPushMatrix();
                    rlRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
                    rlRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
                    rlRotatef(rotation.z, 0.0f, 0.0f, 1.0f);

                    DrawCube((Vector3){ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, SKYBLUE);
                    DrawCubeWires((Vector3){ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, DARKBLUE);
                rlPopMatrix();
            EndMode3D();

            DrawText("Hello world", 300, 100, 20, WHITE);

            if (showWindow) {
                if (GuiWindowBox(panelBounds, "Scene Settings")) {
                    showWindow = false;
                }

                GuiCheckBox((Rectangle){ panelBounds.x + 15, panelBounds.y + 35, 20, 20 }, "Auto-Rotate", &autoSpin);

                GuiLabel((Rectangle){ panelBounds.x + 15, panelBounds.y + 65, 150, 20 }, "Background Color:");
                GuiColorPicker((Rectangle){ panelBounds.x + 15, panelBounds.y + 88, 150, 110 }, NULL, &bgColor);

                if (GuiButton((Rectangle){ panelBounds.x + 15, panelBounds.y + 210, 180, 26 }, "Reset View & Color")) {
                    rotation = (Vector3){ 0.0f, 0.0f, 0.0f };
                    camera.position.z = 6.0f;
                    bgColor = RAYWHITE;
                }
            } else {
                if (GuiButton((Rectangle){ 15, 15, 120, 30 }, "Open Settings")) {
                    showWindow = true;
                }
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
