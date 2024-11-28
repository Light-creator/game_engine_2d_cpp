#pragma once

#include <SDL2/SDL.h>

#include "../ECS.hpp"
#include "position.hpp"

class collider_component_t: public component_t {
public:
  SDL_Rect collider_;
  transform_component_t* transform_;
  
  std::string tag;

public:
  collider_component_t(const char* s): tag(s) {}

  void init() override {
    if(!this->entity_->has_component<transform_component_t>()) {
      this->entity_->add_component<transform_component_t>();
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
    return collider_.x+collider_.w >= other.x && other.x+other.w > collider_.x &&
       collider_.y+collider_.h >= other.y && other.y+other.h > collider_.y;
  }

};
