#include "game.hpp"

int main() {
  game_t game;
  game.init("test_game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, false);
  
  int FPS = 60;
  int frame_delay = 1000 / FPS; 

  uint32_t start_ticks = 0;
  
  while(game.is_running()) {
    start_ticks = SDL_GetTicks();

    game.process_events();
    game.update();
    game.render();
    
    int curr_delay = frame_delay - (SDL_GetTicks() - start_ticks);
    if(curr_delay > 0) SDL_Delay(curr_delay);
  }

  game.quit();

  return 0;
}
