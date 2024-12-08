#pragma once

#include "ECS.hpp"
#include "components/components.hpp"

#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

class map_t {
public:
  size_t rows_ = 0;
  size_t cols_ = 0;
  
  std::vector<entity_t> tiles_;
public:
  map_t(size_t rows, size_t cols): rows_(rows), cols_(cols) {}
  
  void load(const char* file_path, const char* tileset, int w, int h, int scale) {
    std::ifstream file(file_path);
    if(!file.is_open()) {
      std::cout << "File " << file_path << " does not exists\n";
      return;
    }
    
    std::string line;
    std::string delim = " ";
    std::string tk;
    int row = 0;
    size_t pos_start = 0, pos_end;

    while(std::getline(file, line)) {
      pos_start = 0;
      int col = 0;
      while((pos_end = line.find(delim, pos_start)) != std::string::npos) {
        tk = line.substr(pos_start, pos_end - pos_start);
        
        int src_y = tk[0]-'0';
        int src_x = tk[1]-'0';

        src_x *= w;
        src_y *= h;
        
        game_t::add_tile(tileset, src_x, src_y, col*w*scale, row*h*scale, w, h, scale);

        pos_start = pos_end+1;
        col++;
      }
      row++;
    }

    file.close();
  }
};
