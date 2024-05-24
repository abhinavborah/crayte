#include "display.h"
#include "vector.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

//////////////////////////////////////
/// DECLARE AN ARRAY OF VECTOR POINTS
//////////////////////////////////////

const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

float fov_factor = 128;

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

  // Start loading my array of vectors
  // From -1 to 1 (in this 9*9*9 cube)
  int point_count = 0;
  for (float x = -1; x < 1; x += 0.25) {
    for (float y = -1; y < 1; y += 0.25) {
      for (float z = -1; z < 1; z += 0.25) {
        vec3_t new_point = {x, y, z};
        cube_points[point_count++] = new_point;
      }
    }
  }
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

// Function that receives a 3d object and returns a 2d projection
vec2_t project(vec3_t point) {
  vec2_t projected_point;
  projected_point.x = (fov_factor * point.x);
  projected_point.y = (fov_factor * point.y);
  return projected_point;
}

void update(void) {
  for (int i = 0; i < N_POINTS; i++) {
    vec3_t point = cube_points[i];

    // Project the current point
    vec2_t projected_point = project(point);

    // Save the projected 2d vector in the array of projected points
    projected_points[i] = projected_point;
  }
}

void render(void) {
  draw_grid();

  // Loop through all the projected_points and render them
  for (int i = 0; i < N_POINTS; i++) {
    vec2_t projected_point = projected_points[i];
    draw_rectangle(projected_point.x + (window_width / 2),
                   projected_point.y + (window_height / 2), 4, 4, 0xffffff00);
  }
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
