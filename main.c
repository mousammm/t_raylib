#include "raylib.h"

#include "raymath.h"
#include "rlgl.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <style_jungle.h>

static void BeginPortalMode3D(Vector3 eye, Vector3 bottomLeft, Vector3 bottomRight, Vector3 topLeft, float nearPlane, float farPlane);
static void EndPortalMode3D(void);

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "game");
    GuiLoadStyleDefault();
    GuiLoadStyleJungle();

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.5f, 7.0f };
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 archBottomLeft  = { -1.5f, 0.0f, 0.0f };
    Vector3 archBottomRight = {  1.5f, 0.0f, 0.0f };
    Vector3 archTopLeft     = { -1.5f, 4.0f, 0.0f };

    Vector3 portalA = { 0.0f, 0.0f, 0.0f };
    Vector3 portalB = { 0.0f, 0.0f, -60.0f };
    RenderTexture2D rtPortalView = LoadRenderTexture(480, 640);

    bool showMessageBox = false;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        float time = (float)GetTime();

        Vector3 offset = Vector3Subtract(portalB, portalA);
        Vector3 eyeInB = Vector3Add(camera.position, offset);
        Vector3 blInB = Vector3Add(archBottomLeft, offset);
        Vector3 brInB = Vector3Add(archBottomRight, offset);
        Vector3 tlInB = Vector3Add(archTopLeft, offset);

        BeginTextureMode(rtPortalView);

            ClearBackground((Color){ 100, 5, 20, 255 });

            BeginPortalMode3D(eyeInB, blInB, brInB, tlInB, 0.05f, 100.0f);

                DrawGrid(30, 0.8f);

                Vector3 corePos = Vector3Add(portalB, (Vector3){ 0.0f, 2.0f + sinf(time * 2.5f) * 0.4f, -4.0f });
                DrawSphere(corePos, 1.2f, PURPLE);
                DrawSphereWires(corePos, 1.25f, 16, 16, MAGENTA);

                for (int i = 0; i < 4; i++)
                {
                    float angle = time * 1.5f + i * (PI / 2.0f);
                    Vector3 pos = Vector3Add(portalB, (Vector3){
                        sinf(angle) * 2.5f,
                        2.0f + cosf(time * 3.0f + i) * 0.5f,
                        -4.0f + cosf(angle) * 2.5f });

                    DrawCube(pos, 0.5f, 0.5f, 0.5f, LIME);
                    DrawCubeWires(pos, 0.52f, 0.52f, 0.52f, DARKGREEN);
                }

            EndPortalMode3D();

        EndTextureMode();

        BeginDrawing();

            ClearBackground(RED);

            BeginMode3D(camera);

                DrawGrid(20, 1.0f);

                DrawCube((Vector3){ -3.5f, 2.0f, 0.0f }, 0.8f, 4.0f, 0.8f, DARKGRAY);
                DrawCubeWires((Vector3){ -3.5f, 2.0f, 0.0f }, 0.8f, 4.0f, 0.8f, ORANGE);
                DrawCube((Vector3){ 3.5f, 2.0f, 0.0f }, 0.8f, 4.0f, 0.8f, DARKGRAY);
                DrawCubeWires((Vector3){ 3.5f, 2.0f, 0.0f }, 0.8f, 4.0f, 0.8f, ORANGE);

                DrawCubeWires((Vector3){ 0.0f, 2.0f, 0.0f }, 3.2f, 4.2f, 0.2f, GOLD);
                DrawCube((Vector3){ 0.0f, 0.05f, 0.0f }, 3.4f, 0.1f, 0.6f, MAROON);

                DrawCube((Vector3){ 0.0f, 2.0f, -0.05f }, 3.1f, 4.1f, 0.05f, MAROON);

                rlSetTexture(rtPortalView.texture.id);
                rlBegin(RL_QUADS);
                    rlColor4ub(255, 255, 255, 255);
                    rlNormal3f(0.0f, 0.0f, 1.0f);
                    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(archBottomLeft.x, archBottomLeft.y, archBottomLeft.z);
                    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(archBottomRight.x, archBottomRight.y, archBottomRight.z);
                    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(archBottomRight.x, 4.0f, archBottomRight.z);
                    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(archTopLeft.x, archTopLeft.y, archTopLeft.z);
                rlEnd();
                rlSetTexture(0);

            EndMode3D();

            if (GuiButton((Rectangle){ 20, 20, 120, 30 }, "Click This!")) showMessageBox = true;
            if (showMessageBox) {
                int btnActive = -1;
                GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
                    "Message Box", "This is a Message ;)", "Nice;Cool", &btnActive);
                if (btnActive >= 0) showMessageBox = false;
            }

        EndDrawing();
    }

    UnloadRenderTexture(rtPortalView);

    CloseWindow();

    return 0;
}

static void BeginPortalMode3D(Vector3 eye, Vector3 bottomLeft, Vector3 bottomRight, Vector3 topLeft, float nearPlane, float farPlane)
{
    Vector3 right = Vector3Normalize(Vector3Subtract(bottomRight, bottomLeft));
    Vector3 up = Vector3Normalize(Vector3Subtract(topLeft, bottomLeft));
    Vector3 normal = Vector3Normalize(Vector3CrossProduct(right, up));

    Vector3 toBL = Vector3Subtract(bottomLeft, eye);
    Vector3 toBR = Vector3Subtract(bottomRight, eye);
    Vector3 toTL = Vector3Subtract(topLeft, eye);

    float dist = -Vector3DotProduct(toBL, normal);
    if (dist < 0.01f) dist = 0.01f;

    float scale = nearPlane/dist;

    rlDrawRenderBatchActive();

    rlMatrixMode(RL_PROJECTION);
    rlPushMatrix();
    rlSetMatrixProjection(MatrixFrustum(
        Vector3DotProduct(right, toBL)*scale, Vector3DotProduct(right, toBR)*scale,
        Vector3DotProduct(up, toBL)*scale, Vector3DotProduct(up, toTL)*scale,
        nearPlane, farPlane));

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();
    rlMultMatrixf(MatrixToFloat(MatrixLookAt(eye, Vector3Subtract(eye, normal), up)));

    rlEnableDepthTest();
}

static void EndPortalMode3D(void)
{
    rlDrawRenderBatchActive();
    rlMatrixMode(RL_PROJECTION);
    rlPopMatrix();
    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();
    rlDisableDepthTest();
}
