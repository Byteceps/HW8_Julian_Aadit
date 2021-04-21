/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#pragma once

#include <list>
#include <memory>

class HTree {
 public:
  using tree_ptr_t = std::shared_ptr<const HTree>;
  enum class Direction { LEFT, RIGHT };
  using path_t = std::list<Direction>;
  using possible_path_t = std::unique_ptr<path_t>;
  using key_t = int;
  using value_t = uint64_t;


  // Initialize with a key and a value:
  HTree(key_t key,
        value_t value,
        tree_ptr_t left = nullptr,
        tree_ptr_t right = nullptr)
  : key_(key), value_(value), left_(left), right_(right)
  {}

  ~HTree() = default;

  // Return key in current node:
  int get_key() const { return key_; };

  // Return value in current node
  uint64_t get_value() const { return value_; }

  int get_height() const {
    int left = 0;
    int right = 0;

    if(left_ != nullptr){
      left = left_->get_height();
    }
    if(right_ != nullptr){
      right = right_->get_height();
    }
    
    if(left >= right){
      return left + 1;
    }
    else{
      return right + 1;
    } 
  }
  

  // Return the child of this node indicated by dir.
  // If the child is nullptr (current node is a leaf), returns nullptr.
  tree_ptr_t get_child(Direction dir) const
  {
    return (dir == Direction::LEFT)? left_ : right_;
  }

  // Return a pointer to a list of directions from root to
  // a node of a given key.
  // If key not contained in this tree, returns nullptr
  possible_path_t path_to(key_t key) const;

 private:
  key_t key_;
  value_t value_;
  tree_ptr_t left_;
  tree_ptr_t right_;
};
