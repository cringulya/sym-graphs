#include "app.h"
#include "Core/display.h"

void App::update(float t, float dt) {
  display.clear();
  display.update();
}

void App::draw(float t, float dt) {
  glBegin(GL_TRIANGLES);
  glColor3f(1, 0, 0);
  glVertex2f(-0.5f, -0.5f);
  glColor3f(0, 1, 0);
  glVertex2f(0.5f, -0.5f);
  glColor3f(0, 0, 1);
  glVertex2f(0.0f, 0.5f);
  glEnd();
}
