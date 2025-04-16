#include "Core/display.h"
#include "Core/logger.h"
#include "Core/sdlapp.h"
#include "Core/ui/button.h"
#include "app.h"
#include <iostream>

int main(int argc, char *argv[]) {

  auto logger = Logger::getDefault();
  logger->setLevel(LOG_LEVEL_INFO);
  logger->message(LOG_LEVEL_INFO, "heh");

  SDLAppInit("kek", "shmek");
  display.enableVsync(1);
  display.enableResize(1);
  display.enableFrameless(1);
  display.enableAlpha(1);
  display.enableHighDPIAwareness(1);
  display.setClearColour({0.1f, 0.2f, 0.3f});

  display.init("kek", 1000, 1000, -1);

  App app;
  app.run();

  display.quit();
  return 0;
}
