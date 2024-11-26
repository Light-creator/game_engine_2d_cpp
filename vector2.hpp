#pragma once

#include <iostream>

struct vec2_t {
  int x_ = 0, y_ = 0;

  vec2_t(int x, int y): x_(x), y_(y) {}
  vec2_t() = default;
  
  vec2_t& operator+=(vec2_t& v);
  vec2_t& operator-=(vec2_t& v);
  vec2_t& operator*=(vec2_t& v);
  vec2_t& operator/=(vec2_t& v);

  vec2_t operator+(vec2_t& v);
  vec2_t operator-(vec2_t& v);
  vec2_t operator*(vec2_t& v);
  vec2_t operator/(vec2_t& v);

  std::ostream& operator<<(std::ostream& os);
};
