#include "game.hpp"
#include "components/collider.hpp"
#include "components/tile.hpp"
#include "vector2.hpp"
#include "map.hpp"

#include "ECS.hpp"

#include "components/components.hpp"

#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>

SDL_Renderer* game_t::renderer_ = nullptr;
SDL_Event game_t::event_;

ecs_manager_t manager;

auto& tile(manager.add_entity());

auto& player_(manager.add_entity());
// auto& block_(manager.add_entity());

map_t* map;

enum groups {
  tiles_group_,
  players_group_
};

void player_init();

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
 
  // tile.add_component<tile_component_t>(1, 0, 0, 16, 16);
  
  player_init();
   
  // map = new map_t(10, 10);
  // map->load("./assets/maps/test.txt", "",  16, 16, 2);
  
  is_running_ = true;
  return 0;
}

void player_init() {
  player_.add_component<transform_component_t>();
  
  player_.add_component<sprite_component_t>("/home/light/Projects/cpp/gamedev/game_engine_2d/assets/sprites/characters/player.png", 0, 0);
  player_.get_component<sprite_component_t>().add_animation("idle", 6, 0, 50);
  player_.get_component<sprite_component_t>().add_animation("run_up", 6, 2, 100);
  player_.get_component<sprite_component_t>().add_animation("run_down", 6, 3, 100);
  player_.get_component<sprite_component_t>().add_animation("run_left", 6, 1, 100);
  player_.get_component<sprite_component_t>().change_animation("idle");

  player_.add_component<input_component_t>();
  player_.add_component<collider_component_t>("player");
  player_.add_group(players_group_);
}

bool game_t::is_running() {
  return is_running_;
}

void game_t::add_tile(const char* file_path, int src_x, int src_y, int pos_x, int pos_y, int w, int h, int scale) {
  auto& tile(manager.add_entity());
  tile.add_component<tile_component_t>(
    file_path, src_x, src_y, pos_x, pos_y, w, h, scale
  );
  tile.add_group(tiles_group_);
}


void game_t::process_events() {
  SDL_PollEvent(&game_t::event_);
  switch(game_t::event_.type) {
    case SDL_QUIT:
      is_running_ = false;
      break;
    default: break;
  }
}

void game_t::update() {
  manager.update();

  // if(player_.get_component<collider_component_t>().has_collision(
  //   block_.get_component<collider_component_t>().collider_
  // )) {
  //   player_.get_component<transform_component_t>().velocity_ *= -1;
  // }
  
  manager.refresh();
}

// auto& tiles(manager.get_group(tiles_group_));
auto& players(manager.get_group(players_group_));

void game_t::render() {
  SDL_SetRenderDrawColor(renderer_, 242,240,239, 255);
  SDL_RenderClear(renderer_);
  
  for(auto& p: players) p->draw();

  SDL_RenderPresent(renderer_);
}

void game_t::quit() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
}

