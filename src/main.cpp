#include "app.hpp"
#include "parser/parser.hpp"
#include "raylib.h"
#include <exception>
#include <iostream>

int main(int argc, char *argv[]) {
  try {
    InitWindow(1000, 1000, "sym-graphs");
    SetWindowPosition(1000, 100);
    Camera2D camera{};
    camera.target = {0.0f, 0.0f};
    camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    App app;
    while (!WindowShouldClose()) {
      app.update();
      BeginDrawing();
      BeginMode2D(camera);
      ClearBackground(BLACK);
      app.draw();

      EndMode2D();
      EndDrawing();
    }

    CloseWindow();
  } catch (std::exception const &e) {
    std::cerr << e.what();
  }

  return 0;
}
