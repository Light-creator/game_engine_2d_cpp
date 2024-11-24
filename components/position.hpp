#pragma once

#include "../ECS.hpp"

class position_component_t: public component_t {
public:
  int x, y;

  void init() override {
    x = 0; y = 0;
  }

  void update() override {
    x++; y++;
  }
};
