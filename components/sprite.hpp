#pragma once

#include <SDL2/SDL.h>

#include "../ECS.hpp"
#include "../texture_manager.hpp"

#include "position.hpp"

class sprite_component_t: public component_t {
private:
  SDL_Texture* texture_;  
  SDL_Rect src_r_, dst_r_;
  
  position_component_t* pos_;

public:
  sprite_component_t(const char* file_path) {
    texture_ = texture_manager_t::load_texture(file_path);
    src_r_.x = src_r_.y = 0;
  }

  sprite_component_t(const char* file_path, int x, int y) {
    texture_ = texture_manager_t::load_texture(file_path);
    src_r_.x = x;
    src_r_.y = y;
  }

  void init() override {
    pos_ = &entity_->get_component<position_component_t>();
    src_r_.w = src_r_.h = 64;
    dst_r_.w = dst_r_.h = 128;
  }

  void update() override {
    dst_r_.x = pos_->x_;
    dst_r_.y = pos_->y_;
  }

  void draw() override {
    texture_manager_t::draw(texture_, src_r_, dst_r_);
  }
};
