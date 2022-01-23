#ifndef H_WORLD
#define H_WORLD

#include "utils.hpp"
#include "cell.hpp"

struct World {
  World(int cell_size);
  std::map<std::array<int, 2>, Cell*> cells;
  int cell_size;
  int generations = 0;
  bool running = false;
  bool step = false;
  void update();
  void draw_grid_lines();
  void draw_cells();
  void create_cell(int, int);
  void next_generation();
  void process_input();
  void commit_alive_states();
  NeighborStates get_neighbor_states(Cell*);
};

#endif
