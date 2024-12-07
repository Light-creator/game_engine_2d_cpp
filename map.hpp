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
        
        int num = stoi(tk);
        int src_y = num/10;
        int src_x = num%10;
        
        game_t::add_tile(tileset, src_x, src_y, col*w*scale, row*h*scale, w, h, 2);

        pos_start = pos_end+1;
        col++;
      }
      row++;
    }

    file.close();
  }
};
