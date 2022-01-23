#include "utils.hpp"

int round_to_nearest_cell(int x, int cell_size) {
  int ten = x % 10;
  return x - ten;
}

