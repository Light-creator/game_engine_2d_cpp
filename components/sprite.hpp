#pragma once

#include <SDL2/SDL.h>

#include "../ECS.hpp"
#include "../texture_manager.hpp"

#include "position.hpp"

class sprite_component_t: public component_t {
private:
  SDL_Texture* texture_;  
  SDL_Rect src_r_, dst_r_;
  
  transform_component_t* transform_;
  
  bool is_animated_ = false;
  int frames_ = 0;
  int speed_ = 100;
  int counter_ = 0;

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
 
  sprite_component_t(const char* file_path, int x, int y, int frames, int speed): 
    is_animated_(true), frames_(frames), speed_(speed) {
    texture_ = texture_manager_t::load_texture(file_path);
    src_r_.x = x;
    src_r_.y = y;
  }

  void init() override {
    transform_ = &entity_->get_component<transform_component_t>();
    src_r_.w = transform_->w_; 
    src_r_.h = transform_->h_;
    dst_r_.w = transform_->w_ * transform_->scale_;
    dst_r_.h = transform_->h_ * transform_->scale_;
  }

  void update() override {
    if(is_animated_) {
      src_r_.x = src_r_.w * static_cast<int>((SDL_GetTicks() / speed_) % frames_);
      // std::cout << src_r_.x << "\n";
    }

    dst_r_.x = transform_->pos_.x_;
    dst_r_.y = transform_->pos_.y_;
  }

  void draw() override {
    texture_manager_t::draw(texture_, src_r_, dst_r_);
  }
};
