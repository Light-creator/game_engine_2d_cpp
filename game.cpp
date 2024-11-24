#include "game.hpp"
#include "ecs_manager.hpp"

#include "components/components.hpp"

#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>

SDL_Renderer* game_t::renderer_ = nullptr;

ecs_manager_t manager;
auto& player_(manager.add_entity());

int game_t::init(const char* title, int x, int y, int w, int h, bool fullscreen) {
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Game init error\n";
    return 1;
  }
    
  uint32_t flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
  window_ = SDL_CreateWindow(title, x, y, w, h, flags);
  if(!window_) {
    std::cerr << "Window init error\n";
    return 1;
  }

  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  if(!renderer_) {
    std::cerr << "Renderer init error\n";
    return 1;
  }
  
  player_.add_component<position_component_t>();
  player_.add_component<sprite_component_t>("/home/light/Projects/cpp/gamedev/game_engine_2d/assets/sprites/characters/player.png");
  
  is_running_ = true;
  return 0;
}

bool game_t::is_running() {
  return is_running_;
}

void game_t::process_events() {
  SDL_Event e;
  SDL_PollEvent(&e);
  switch(e.type) {
    case SDL_QUIT:
      is_running_ = false;
      break;
    default: break;
  }
}

void game_t::update() {
  manager.update();

  manager.refresh();
}

void game_t::render() {
  SDL_SetRenderDrawColor(renderer_, 242,240,239, 255);
  SDL_RenderClear(renderer_);
    
  manager.draw();

  SDL_RenderPresent(renderer_);
}

void game_t::quit() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
}

