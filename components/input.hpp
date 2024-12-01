#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

#include "../ECS.hpp"
#include "position.hpp"
#include "../game.hpp"
#include "sprite.hpp"

class input_component_t: public component_t {
private:
  transform_component_t* transform_;
  sprite_component_t* sprite_;

public:
  void init() override {
    transform_ = &this->entity_->get_component<transform_component_t>();
    sprite_ = &this->entity_->get_component<sprite_component_t>();
  }

  void update() override {
    if(game_t::event_.type == SDL_KEYDOWN) {
      switch(game_t::event_.key.keysym.sym) {
        case SDLK_w: 
          transform_->set_vel_y(-1); 
          sprite_->change_animation("run_up");
          break;
        case SDLK_s: 
          transform_->set_vel_y(1); 
          sprite_->change_animation("run_down");
          break;
        case SDLK_d: 
          transform_->set_vel_x(1); 
          sprite_->change_animation("run_left");
          break;
        case SDLK_a: 
          transform_->set_vel_x(-1); 
          sprite_->flip_ = SDL_FLIP_HORIZONTAL;
          sprite_->change_animation("run_left");
          break;
        default: break;
      }
    }

    if(game_t::event_.type == SDL_KEYUP) {
      switch(game_t::event_.key.keysym.sym) {
        case SDLK_w: 
          transform_->set_vel_y(0); 
          sprite_->change_animation("idle");
          break;
        case SDLK_s: 
          transform_->set_vel_y(0); 
          sprite_->change_animation("idle");
          break;
        case SDLK_d: 
          transform_->set_vel_x(0); 
          sprite_->change_animation("idle");
          break;
        case SDLK_a: 
          transform_->set_vel_x(0); 
          sprite_->flip_ = SDL_FLIP_NONE;
          sprite_->change_animation("idle");
          break;
        default: break;
      }
    }
  }
};
