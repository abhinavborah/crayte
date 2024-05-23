#include "display.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

bool is_running = false;

// Color Buffer to store the pixel values
void setup(void) {
  // Allocate memory for the color buffer
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  // Create an SDL texture to display the color buffer
  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           window_width, window_height);
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      is_running = false;
      break;
    }
  }
}

void update(void) {
  // TODO:
}

void render(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
  SDL_RenderClear(renderer);

  draw_grid();

  draw_pixel(200, 300, 0xff00ffff);

  render_color_buffer();
  clear_color_buffer(0xff000000);

  SDL_RenderPresent(renderer);
}

int main(void) {
  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();
  return 0;
}
