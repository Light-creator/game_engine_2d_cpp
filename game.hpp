#pragma once

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
  
  static SDL_Renderer* renderer_;
};
