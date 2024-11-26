#include "vector2.hpp"

vec2_t& vec2_t::operator+=(vec2_t& v) {
  x_ += v.x_;
  y_ += v.y_;
  return *this;
}

vec2_t& vec2_t::operator-=(vec2_t& v) {
  x_ -= v.x_;
  y_ -= v.y_;
  return *this;   
}

vec2_t& vec2_t::operator*=(vec2_t& v) {
  x_ *= v.x_;
  y_ *= v.y_;
  return *this;  
}

vec2_t& vec2_t::operator/=(vec2_t& v) {
  x_ /= v.x_;
  y_ /= v.y_;
  return *this;
}

vec2_t vec2_t::operator+(vec2_t& v) {
  vec2_t res = *this;
  res += v;
  return res;
}

vec2_t vec2_t::operator-(vec2_t& v) {
  vec2_t res = *this;
  res -= v;
  return res;
}

vec2_t vec2_t::operator*(vec2_t& v) {
  vec2_t res = *this;
  res *= v;
  return res;
}

vec2_t vec2_t::operator/(vec2_t& v) {
  vec2_t res = *this;
  res /= v;
  return res;
}

std::ostream& vec2_t::operator<<(std::ostream& os) {
  os << "(" << x_ << " " << y_ << ")";
  return os;
}

