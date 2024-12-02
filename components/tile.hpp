#pragma once

#include "../ECS.hpp"
#include "collider.hpp"
#include "position.hpp"
#include "sprite.hpp"

class tile_component_t: public component_t {
public:
  int type_id_;
  collider_component_t* collider_;
  sprite_component_t* sprite_;
  transform_component_t* transform_;

  std::string path;

  SDL_Rect r_;
public:
  tile_component_t() = default;

  tile_component_t(int type_id, int x, int y, int w, int h): type_id_(type_id) {
    r_.x = x;
    r_.y = y;
    r_.w = w;
    r_.h = h;

    switch(type_id_) {
      case 1:
        path = "assets/sprites/tilesets/floors/wooden.png";
        break;
      case 2:
        path = "assets/sprites/tilesets/grass.png";
        break;
      default: break;
    }
  }

  void init() override {
    entity_->add_component<transform_component_t>(r_.w, r_.h, 2, r_.x, r_.y);
    transform_ = &entity_->get_component<transform_component_t>();

    entity_->add_component<collider_component_t>();
    collider_ = &entity_->get_component<collider_component_t>();
    
    entity_->add_component<sprite_component_t>((const char*)path.c_str(), 0, 0);
    sprite_ = &entity_->get_component<sprite_component_t>();
  }
};
