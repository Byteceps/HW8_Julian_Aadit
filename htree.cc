/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"

// Return an optional list of directions from root to a node of a given key.
// If key not contained in this tree, returns nullptr
HTree::possible_path_t
HTree::path_to(key_t key) const
{
  if (key_ == key) {
    return possible_path_t(new path_t());
  }

  if (left_) {
    auto ret = left_->path_to(key);
    if (ret) {
      ret->push_front(Direction::LEFT);
      return ret;
    }
  }

  if (right_) {
    auto ret = right_->path_to(key);
    if (ret) {
      ret->push_front(Direction::RIGHT);
      return ret;
    }
  }

  return nullptr;
}
