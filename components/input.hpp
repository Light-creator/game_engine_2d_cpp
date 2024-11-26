#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>

#include "../ECS.hpp"
#include "position.hpp"
#include "../game.hpp"

class input_component_t: public component_t {
private:
  transform_component_t* transform_;
public:
  void init() override {
    transform_ = &this->entity_->get_component<transform_component_t>();
  }

  void update() override {
    if(game_t::event_.type == SDL_KEYDOWN) {
      switch(game_t::event_.key.keysym.sym) {
        case SDLK_w: 
          transform_->set_vel_y(-1); 
          break;
        case SDLK_s: 
          transform_->set_vel_y(1); 
          break;
        case SDLK_d: 
          transform_->set_vel_x(1); 
          break;
        case SDLK_a: 
          transform_->set_vel_x(-1); 
          break;
        default: break;
      }
    }

    if(game_t::event_.type == SDL_KEYUP) {
      switch(game_t::event_.key.keysym.sym) {
        case SDLK_w: 
          transform_->set_vel_y(0); 
          break;
        case SDLK_s: 
          transform_->set_vel_y(0); 
          break;
        case SDLK_d: 
          transform_->set_vel_x(0); 
          break;
        case SDLK_a: 
          transform_->set_vel_x(0); 
          break;
        default: break;
      }
    }
  }
};
