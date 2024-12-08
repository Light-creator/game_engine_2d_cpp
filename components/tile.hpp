#pragma once

#include "../ECS.hpp"
#include "../texture_manager.hpp"
#include "../vector2.hpp"

class tile_component_t: public component_t {
public:
  int src_x_, src_y_, pos_x_, pos_y_;
  int w_, h_;
  int scale_;

  SDL_Texture* texture_;
  SDL_Rect src_r_, dst_r_;

  vec2_t pos_;
  
  SDL_RendererFlip flip_ = SDL_FLIP_NONE;

public:
  tile_component_t() = default;

  tile_component_t(const char* file_path, int src_x, int src_y, int pos_x, int pos_y, int w, int h, int scale): 
    src_x_(src_x), src_y_(src_y), pos_x_(pos_x), pos_y_(pos_y), w_(w), h_(h), scale_(scale) {
    
    texture_ = texture_manager_t::load_texture(file_path);
  }

  void init() override {
    pos_.x_ = pos_x_;
    pos_.y_ = pos_y_;

    src_r_.x = src_x_;
    src_r_.y = src_y_;
    src_r_.w = w_;
    src_r_.h = h_;

    dst_r_.x = pos_x_;
    dst_r_.y = pos_y_;
    dst_r_.w = w_*scale_;
    dst_r_.h = h_*scale_;
  }

  void update() override {
    dst_r_.x = pos_.x_ - game_t::camera_.x;
    dst_r_.y = pos_.y_ - game_t::camera_.y;
  }

  void draw() override {
    texture_manager_t::draw(texture_, src_r_, dst_r_, flip_);
  }
};
