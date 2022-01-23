#ifndef H_CELL
#define H_CELL

struct NeighborStates {
  bool top_left;
  bool top;
  bool top_right;
  bool left;
  bool right;
  bool bottom_left;
  bool bottom;
  bool bottom_right;
};

struct Cell {
  Cell(int x, int y);
  bool is_alive = false;
  bool changed_next_generation = false;
  int x;
  int y;
  void update(NeighborStates ns);
  void commit_alive_state();
};

#endif
