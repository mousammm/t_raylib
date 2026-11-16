#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

#include <rlgl.h>
#include <style_jungle.h>

#ifndef PLATFORM_WEB
#define FONT_PATH "asset/fonts/iosevka-regular.ttf"
#endif

int main(void)
{
    const int screenWidth  = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "3D Scene — raylib");

#ifndef PLATFORM_WEB
    GuiLoadStyleDefault();
    GuiLoadStyleJungle();
    Font font = LoadFontEx(FONT_PATH, 48, 0, 250);
    if (font.texture.id != GetFontDefault().texture.id) {
        SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
        GuiSetFont(font);
    }
#endif

    Camera3D camera = { 0 };
    camera.position   = (Vector3){ 0.0f, 6.0f, 12.0f };
    camera.target     = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.up         = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy       = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Orbiting cubes
    const int cubeCount = 6;
    Vector3 cubePos[cubeCount];
    Color   cubeCol[cubeCount];
    for (int i = 0; i < cubeCount; i++) {
        cubeCol[i] = ColorFromHSV((float)i / cubeCount * 360.0f, 0.7f, 0.9f);
    }

    SetTargetFPS(60);
    float t = 0.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        t += dt;

        // Camera orbit
        float camAngle = t * 0.15f;
        camera.position.x = sinf(camAngle) * 14.0f;
        camera.position.z = cosf(camAngle) * 14.0f;
        camera.position.y = 7.0f + sinf(t * 0.4f) * 1.5f;
        camera.target     = (Vector3){ 0.0f, 2.0f, 0.0f };

        // Cube orbits
        for (int i = 0; i < cubeCount; i++) {
            float a = t * 0.8f + (float)i / cubeCount * 2.0f * PI;
            float r = 3.5f;
            cubePos[i].x = cosf(a) * r;
            cubePos[i].z = sinf(a) * r;
            cubePos[i].y = 2.0f + sinf(a * 2.0f + (float)i) * 1.2f;
        }

        // Moving light marker
        Vector3 lightPos = {
            sinf(t * 0.7f) * 6.0f,
            8.0f,
            cosf(t * 0.7f) * 6.0f
        };

        BeginDrawing();
        ClearBackground(DARKGRAY);

        BeginMode3D(camera);

            DrawGrid(30, 1.0f);

            // Central object: rotating wireframe sphere (replaces DrawTorusKnot)
            Color coreCol = ColorFromHSV(fmodf(t * 30.0f, 360.0f), 0.6f, 0.9f);
            DrawSphere((Vector3){ 0, 2.0f, 0 }, 1.2f, Fade(coreCol, 0.85f));
            DrawSphereWires((Vector3){ 0, 2.0f, 0 }, 1.25f, 16, 16, coreCol);

            // Orbiting cubes with per-cube rotation
            for (int i = 0; i < cubeCount; i++) {
                rlPushMatrix();
                    rlTranslatef(cubePos[i].x, cubePos[i].y, cubePos[i].z);
                    rlRotatef(t * 120.0f + i * 30.0f, 1.0f, 1.0f, 0.0f);
                    DrawCube((Vector3){ 0, 0, 0 }, 0.8f, 0.8f, 0.8f, cubeCol[i]);
                    DrawCubeWires((Vector3){ 0, 0, 0 }, 0.8f, 0.8f, 0.8f, BLACK);
                rlPopMatrix();
            }

            DrawSphere(lightPos, 0.15f, YELLOW);

        EndMode3D();

        // HUD
        DrawRectangle(0, 0, screenWidth, 60, Fade(BLACK, 0.4f));
        DrawTextEx(GuiGetFont(), "3D Scene — Orbiting Cubes",
                   (Vector2){ 20, 16 }, 24, 1.0f, RAYWHITE);

        GuiStatusBar((Rectangle){ 0, (float)screenHeight - 24, (float)screenWidth, 24 },
                     TextFormat("FPS: %d | Camera angle: %.1f°", GetFPS(), camAngle * RAD2DEG));

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
