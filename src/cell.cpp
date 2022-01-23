#include "cell.hpp"
#include "world.hpp"
#include "utils.hpp"

Cell::Cell(int x, int y) {
  this->x = x;
  this->y = y;
}

void Cell::update(NeighborStates ns) {
  bool tl = ns.top_left;
  bool t = ns.top;
  bool tr = ns.top_right;
  bool l = ns.left;
  bool r = ns.right;
  bool bl = ns.bottom_left;
  bool b = ns.bottom;
  bool br = ns.bottom_right;

  int num_neighbors = tl + t + tr + l + r + bl + b + br;
  this->changed_next_generation = (this->is_alive && (num_neighbors != 2 && num_neighbors != 3)) || (!this->is_alive && num_neighbors == 3);
}

void Cell::commit_alive_state() {
  if (this->changed_next_generation) {
    this->is_alive = !this->is_alive;
    this->changed_next_generation = false;
  }
}
