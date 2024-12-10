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
SDL_Rect game_t::camera_ = {0, 0, 0, 0};
int game_t::screen_h_ = 0;
int game_t::screen_w_ = 0;

ecs_manager_t game_t::manager_;

auto& tile(game_t::manager_.add_entity());
auto& player_(game_t::manager_.add_entity());

map_t* map;

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

  screen_h_ = h;
  screen_w_ = w;
  camera_.w = w;
  camera_.h = h;

  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  if(!renderer_) {
    std::cerr << "Renderer init error\n";
    return 1;
  }
 
  player_init();
   
  map = new map_t(12, 12);
  map->load("./assets/maps/test.txt", "./assets/tileset/FieldsTileset.png",  32, 32, 4);
  
  is_running_ = true;
  return 0;
}

void player_init() {
  player_.add_component<transform_component_t>(48, 60, 2, game_t::screen_w_/2, game_t::screen_h_/2);
 
  player_.add_component<sprite_component_t>("/home/light/Projects/cpp/gamedev/game_engine_2d/assets/sprites/characters/player.png", 0, 0);
  player_.get_component<sprite_component_t>().add_animation("idle", 6, 0, 50);
  player_.get_component<sprite_component_t>().add_animation("run_up", 6, 2, 100);
  player_.get_component<sprite_component_t>().add_animation("run_down", 6, 3, 100);
  player_.get_component<sprite_component_t>().add_animation("run_left", 6, 1, 100);
  player_.get_component<sprite_component_t>().change_animation("idle");
 
  player_.add_component<input_component_t>();
  player_.add_component<collider_component_t>();
  player_.add_group(game_t::players_group_);
}

bool game_t::is_running() {
  return is_running_;
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

auto& colliders(game_t::manager_.get_group(game_t::colliders_group_));

void game_t::update() {
  game_t::manager_.update();
  
  camera_.x = player_.get_component<transform_component_t>().pos_.x_ - screen_w_/2;
  camera_.y = player_.get_component<transform_component_t>().pos_.y_ - screen_h_/2;
  
  if(camera_.x < 0) camera_.x = 0;
  if(camera_.y < 0) camera_.y = 0;
  if(camera_.x > screen_w_) camera_.x = screen_w_; 
  if(camera_.y > screen_h_) camera_.y = screen_h_;
  
  int idx = 0;
  // std::cout << idx << "\n";
  for(auto& c: colliders) {
    // std::cout << idx++ << "\n";
    if(player_.get_component<collider_component_t>().has_collision(
      c->get_component<collider_component_t>().collider_
    )) {
      collider_component_t* cc_ = &c->get_component<collider_component_t>();
      std::cout << "collision: " << cc_->y_ << " " << cc_->x_ << "\n";
    }
  }

  // if(player_.get_component<collider_component_t>().has_collision(
  //   block_.get_component<collider_component_t>().collider_
  // )) {
  //   player_.get_component<transform_component_t>().velocity_ *= -1;
  // }
  
  game_t::manager_.refresh();
}

auto& tiles(game_t::manager_.get_group(game_t::tiles_group_));
auto& players(game_t::manager_.get_group(game_t::players_group_));

void game_t::render() {
  SDL_SetRenderDrawColor(renderer_, 242,240,239, 255);
  SDL_RenderClear(renderer_);
  
  for(auto& t: tiles) t->draw();

  for(auto& p: players) p->draw();

  SDL_RenderPresent(renderer_);
}

void game_t::quit() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
}

