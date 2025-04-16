#pragma once

#include "Core/sdlapp.h"

class App : public SDLApp {

  void update(float t, float dt);
  void draw(float t, float dt);
};
