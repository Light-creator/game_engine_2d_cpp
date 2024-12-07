// #pragma once

// // #include "ECS.hpp"

// #include <algorithm>
// #include <memory>
// #include <vector>

// class ecs_manager_t {
// private:
//   std::vector<std::unique_ptr<entity_t>> entities_;

// public:
//   void update() {
//     for(auto& entity: entities_) entity->update();
//   }

//   void draw() {
//     for(auto& entity: entities_) entity->draw();
//   }

//   void refresh() {
//     entities_.erase(std::remove_if(entities_.begin(), entities_.end(), [](const std::unique_ptr<entity_t>& a) {
//       return !a->is_active();
//     }), entities_.end());
//   }

//   entity_t& add_entity() {
//     entity_t* entity = new entity_t();
//     std::unique_ptr<entity_t> ptr(entity);
//     entities_.emplace_back(std::move(ptr));

//     sort(entities_.begin(), entities_.end(), [](const auto& a, const auto& b) {
//       return a->z() < b->z();
//     });
//     return *entity;
//   }
// };
