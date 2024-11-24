#pragma once

#include <SDL2/SDL.h>
#include <array>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

class entity_t;

inline size_t get_component_id() {
  static size_t component_id = 0;
  return component_id++;
}

template<typename T> 
size_t get_component_id() noexcept {
  static size_t component_id = get_component_id();
  return component_id;
}

class component_t {
public:
  entity_t* entity_;
  
  virtual void init() {}
  virtual void update() {}
  virtual void draw() {}

  virtual ~component_t() {}
};

class entity_t {
private:
  bool is_active_ = true;
  std::vector<std::unique_ptr<component_t>> components_; // for update and draw functions
  std::array<component_t*, 32> arr_; // for returning as actual component
  std::unordered_map<size_t, bool> hash_; // for checking has_component?
 
public:
  void update() {
    for(auto& component: components_) component->update();
  }

  void draw() {
    for(auto& component: components_) component->draw();
  }

  template<typename T, typename... Args>
  T& add_component(Args&&... args) {
    T* component(new T(std::forward<Args>(args)...));
    component->entity_ = this;
    std::unique_ptr<component_t> ptr(component);
    components_.emplace_back(std::move(ptr));
      
    arr_[get_component_id<T>()] = component;
    hash_[get_component_id<T>()] = true;
    component->init();
    return *component;
  }

  template<typename T> 
  T& get_component() const {
    auto ptr = arr_[get_component_id<T>()];
    return *static_cast<T*>(ptr); // component_t -> position_component_t (casting to component actual type)
  }

  template<typename T>
  bool has_component() const {
    return hash_[get_component_id<T>()];
  }

  bool is_active() {
    return is_active_;
  }

  void destroy() {
    is_active_ = false;
  }
};




