#include "app.h"
#include "raylib.h"
#include <iostream>

int main(int argc, char *argv[]) {

  InitWindow(1000, 1000, "sym-graphs");
  SetWindowPosition(1000, 100);
  App app;
  Camera2D camera{};
  camera.target = {0.0f, 0.0f};
  camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.f;

  while (!WindowShouldClose()) {
    app.update();
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(RAYWHITE);
    app.draw();

    EndMode2D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
  return 0;
}
