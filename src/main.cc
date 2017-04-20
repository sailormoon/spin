#include <SDL2/SDL.h>
#include <glog/logging.h>
#include <chrono>
#include "scope_guard.h"
#include "util.h"

int main() {
  using namespace kuru;
  CHECK_SDL(SDL_Init(SDL_INIT_EVERYTHING) == 0);
  const scope_guard sdl_quit(SDL_Quit);

  const sdl_ptr<SDL_Window> window(
      SDL_CreateWindow("kuru!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       640, 480, SDL_WINDOW_SHOWN),
      SDL_DestroyWindow);
  CHECK_SDL(window);

  const sdl_ptr<SDL_Renderer> renderer(
      SDL_CreateRenderer(window.get(), -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
      SDL_DestroyRenderer);
  CHECK_SDL(renderer);

  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return 0;
      }
      // state.handle_event(event)
    }

    SDL_RenderClear(renderer.get());
    // state.render();
    SDL_SetRenderDrawColor(renderer.get(), 128, 0, 0, 255);
    SDL_RenderPresent(renderer.get());
  }
}
