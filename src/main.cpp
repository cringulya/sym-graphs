#include "app.hpp"
#include "parser/parser.hpp"
#include "raylib.h"
#include <exception>
#include <iostream>

// TODO:
// - map specificly in edges, make attraction greater for those
// - console args path
// - settings
// - save

int main(int argc, char *argv[]) {
  try {
    InitWindow(1000, 1000, "sym-graphs");
    SetWindowPosition(1000, 100);
    Camera2D camera{0};
    camera.target = {0.0f, 0.0f};
    camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    App app;

    if (argc == 2) {
      app.init(argv[1]);
    } else {
      std::cerr
          << "[Error]: Invalid args\nPut path to serialization as argument"
          << std::endl;
      exit(1);
    }
    while (!WindowShouldClose()) {
      if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
      }

      float wheel = GetMouseWheelMove();
      if (wheel != 0) {
        float zoomFactor = 1.1f;
        float prevZoom = camera.zoom;

        Vector2 mousePosScreen = GetMousePosition();
        Vector2 worldBefore = GetScreenToWorld2D(mousePosScreen, camera);

        if (wheel > 0) {
          camera.zoom *= zoomFactor;
        } else {
          camera.zoom /= zoomFactor;
        }

        // camera.zoom = Clamp(camera.zoom, 0.1f, 10.0f);

        Vector2 worldAfter = GetScreenToWorld2D(mousePosScreen, camera);

        Vector2 worldDelta = Vector2Subtract(worldBefore, worldAfter);
        camera.target = Vector2Add(camera.target, worldDelta);
      }

      BeginDrawing();
      BeginMode2D(camera);
      ClearBackground(BLACK);
      app.draw();

      EndMode2D();
      EndDrawing();
    }

    CloseWindow();
  } catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
