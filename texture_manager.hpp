#pragma once

#include "game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class texture_manager_t {
public:
  static SDL_Texture* load_texture(const char* file_path) {
    SDL_Surface* surface = IMG_Load(file_path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game_t::renderer_, surface);
    SDL_FreeSurface(surface);
    
    return texture;
  }
};
