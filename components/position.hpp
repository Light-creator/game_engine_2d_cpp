#pragma once

#include "../ECS.hpp"

class position_component_t: public component_t {
public:
  int x_, y_;

  void init() override {
    x_ = 0; y_ = 0;
  }

  void update() override {
    x_++; y_++;
  }
};
