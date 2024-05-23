#include "display.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  };

  // Get the current display mode
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);
  window_width = display_mode.w;
  window_height = display_mode.h;

  // Creates an SDL window
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       window_width, window_height, SDL_WINDOW_RESIZABLE);

  if (!window) {
    fprintf(stderr, "Error creating SDL window.\n");
    return false;
  }

  // Create an SDL renderer
  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    fprintf(stderr, "Error creating SDL renderer.\n");
    return false;
  }

  // Set the window to fullscreen
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  return true;
}

// draw a white grid with pixel values multiple of 10
void draw_grid(void) {
  for (int y = 0; y < window_height; y += 20) {
    for (int x = 0; x < window_width; x += 20) {
      color_buffer[(y * window_width) + x] = 0xff444444;
    }
  }
}

void draw_pixel(int x, int y, uint32_t color) {
  if (x < window_width && y < window_height) {
    color_buffer[(y * window_width) + x] = color;
  }
}

// draw a rectangle taking x and y position along with sidth and height as input
void draw_rectangle(int x, int y, int width, int height, uint32_t color) {
  // TODO: implement window res check
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      color_buffer[(y + j) * window_width + x + i] = color;
    }
  }
}

void render_color_buffer(void) {
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    window_width * sizeof(uint32_t));
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      color_buffer[(y * window_width) + x] = color;
    }
  }
}

// Memory Deallocation
void destroy_window(void) {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
