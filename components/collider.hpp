#pragma once

#include <SDL2/SDL.h>

#include "../ECS.hpp"
#include "position.hpp"

class collider_component_t: public component_t {
public:
  SDL_Rect collider_;
  transform_component_t* transform_;
  
  std::string tag;
  int x_, y_, w_, h_, scale_;

public:
  collider_component_t() = default;

  collider_component_t(const char* s): tag(s) {}
  collider_component_t(int x, int y, int w, int h, int scale): x_(x), y_(y), w_(w), h_(h), scale_(scale) {
    // if(!this->entity_->has_component<transform_component_t>()) {
    //   this->entity_->add_component<transform_component_t>(w, h, scale, x, y);
    // }    
  }

  void init() override {
    if(!this->entity_->has_component<transform_component_t>()) {
      this->entity_->add_component<transform_component_t>(x_, y_, scale_, w_, h_);
    }

    transform_ = &this->entity_->get_component<transform_component_t>();
  }
  
  void update() override {
    collider_.x = transform_->pos_.x_;
    collider_.y = transform_->pos_.y_;
    collider_.w = transform_->w_ * transform_->scale_;
    collider_.h = transform_->h_ * transform_->scale_;
  }

  bool has_collision(SDL_Rect& other) const {
    // std::cout << other.x << " " << other.y  << "\n";
    return collider_.x+collider_.w >= other.x && other.x+other.w > collider_.x &&
       collider_.y+collider_.h >= other.y && other.y+other.h > collider_.y;
  }

};
