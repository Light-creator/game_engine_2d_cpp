#include <SDL2/SDL.h>
#include <string>

class animation_t {
public:
  std::string tag_;
  int frames_ = 0;
  int sprite_pos_y_ = 0;
  int speed_ = 0;

public:
  animation_t(const char* tag, int frames, int sprite_pos_y, int speed):
    tag_(tag), frames_(frames), sprite_pos_y_(sprite_pos_y), speed_(speed) {}
};
