#pragma once

#include "../ECS.hpp"
#include "../vector2.hpp"

class transform_component_t: public component_t {
public:
  int w_ = 64, h_ = 64;
  int scale_ = 2;
  vec2_t pos_{0, 0};
  vec2_t velocity_;
  int speed_ = 5;

public:
  transform_component_t() = default;

  transform_component_t(int w, int h, int scale, int x, int y):
    w_(w), h_(h), scale_(scale) {
    pos_.x_ = x;
    pos_.y_ = y;
  }

  void init() override {
    velocity_ *= 0;
  }

  void update() override {
    pos_.x_ += velocity_.x_ * speed_;
    pos_.y_ += velocity_.y_ * speed_;
  }
  
  void set_velocity(int x, int y) {
    velocity_.x_ = x;
    velocity_.y_ = y;
  }

  int x() { return pos_.x_; }
  int y() { return pos_.y_; }

  void set_vel_x(int x) { velocity_.x_ = x; }
  void set_vel_y(int y) { velocity_.y_ = y; }
};
