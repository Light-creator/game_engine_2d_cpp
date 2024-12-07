#pragma once

#include <SDL2/SDL.h>
#include <array>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>

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

class ecs_manager_t;

class entity_t {
private:
  ecs_manager_t& manager_;

  bool is_active_ = true;
  int z_index = 0;
  std::vector<std::unique_ptr<component_t>> components_; // for update and draw functions
  std::array<component_t*, 32> arr_; // for returning as actual component
  std::unordered_map<size_t, bool> hash_; // for checking has_component?
  std::unordered_map<size_t, bool> group_check_; // for checking has_component?
 
public:
  entity_t(ecs_manager_t& manager): manager_(manager) {}

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
    return hash_.find(get_component_id<T>()) != hash_.end();
  }

  bool is_active() {
    return is_active_;
  }

  void set_z_index(int z) {
    z_index = z;
  }

  int z() {
    return z_index;
  }

  void destroy() {
    is_active_ = false;
  }
  
  bool has_group(size_t group_id) {
    return group_check_.find(group_id) != group_check_.end();
  }

  void add_group(size_t group_id);

  void del_group(size_t group_id) {
    group_check_[group_id] = true;
  }
};

class ecs_manager_t {
private:
  std::vector<std::unique_ptr<entity_t>> entities_;
  std::unordered_map<size_t, std::vector<entity_t*>> groups_;

public:
  void update() {
    for(auto& entity: entities_) entity->update();
  }

  void draw() {
    for(auto& entity: entities_) entity->draw();
  }

  void refresh() {  
    for(auto& [k, v]: groups_) {
      v.erase(std::remove_if(v.begin(), v.end(), [k](auto& a) {
        return !a->is_active() || !a->has_group(k);
      }),
      v.end());
    }

    entities_.erase(std::remove_if(entities_.begin(), entities_.end(), [](const std::unique_ptr<entity_t>& a) {
      return !a->is_active();
    }), entities_.end());
  }

  entity_t& add_entity() {
    entity_t* entity = new entity_t(*this);
    std::unique_ptr<entity_t> ptr(entity);
    entities_.emplace_back(std::move(ptr));

    sort(entities_.begin(), entities_.end(), [](const auto& a, const auto& b) {
      return a->z() < b->z();
    });
    return *entity;
  }

  bool has_group(size_t group_id) {
    return groups_.find(group_id) != groups_.end();
  }

  void add_to_group(entity_t* entity_, size_t group_id) {
    if(has_group(group_id)) {
      groups_[group_id].emplace_back(entity_);
    } else {
      std::vector<entity_t*> v;
      v.emplace_back(entity_);
      groups_[group_id] = std::move(v);
    }   
  }

  std::vector<entity_t*>& get_group(size_t group_id) {
    return groups_[group_id];
  }
};







