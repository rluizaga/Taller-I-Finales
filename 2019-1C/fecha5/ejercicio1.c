/***
Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje un
triángulo amarillo del tamaño de la ventana.
***/

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define WIDTH 640
#define HEIGHT 480

int main() {
  SDL_Window *window =
      SDL_CreateWindow("SDL2 GFX", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_Event e;
  int quit = 0;

  const short triangle_x[] = {WIDTH / 2, WIDTH, 0};
  const short triangle_y[] = {0, HEIGHT - 1, HEIGHT - 1};
  const int triangle_n_points = 3;

  while (!quit) {
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    polygonRGBA(renderer, triangle_x, triangle_y, triangle_n_points, 0xff, 0xff,
                0x00, 0xff);

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}