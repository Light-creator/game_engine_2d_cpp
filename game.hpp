#pragma once

#include "components/collider.hpp"
#include <SDL2/SDL.h>

class game_t {
private:
  bool is_running_;
  SDL_Window* window_;

public:
  game_t() {}
  int init(const char* title, int x, int y, int w, int h, bool fullscreen);

  bool is_running();
  
  void process_events();
  void update();
  void render();

  void quit();
  
  static void add_tile(const char* file_path, int src_x, int src_y, int pos_x, int pos_y, int w, int h, int scale);
  
  static SDL_Renderer* renderer_;
  static SDL_Event event_;

  static std::vector<collider_component_t> colliders_;

  static int screen_w_;
  static int screen_h_;

  static SDL_Rect camera_;
};
