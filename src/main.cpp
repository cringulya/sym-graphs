#include "Core/display.h"
#include "Core/logger.h"
#include "Core/sdlapp.h"
#include <iostream>

int main(int argc, char *argv[]) {

  // Log the initialization of SDL2

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("Hello SDL2 with Core", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

  if (!window) {
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255); // blue
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  // Wait for 3 seconds
  SDL_Delay(3000);

  // Cleanup
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
