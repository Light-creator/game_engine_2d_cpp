#include "ECS.hpp"

void entity_t::add_group(size_t group_id) {
  group_check_[group_id] = true;
  manager_.add_to_group(this, group_id);
}
