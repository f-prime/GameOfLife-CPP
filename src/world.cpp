#include "utils.hpp"
#include "world.hpp"
#include "cell.hpp"

void draw_num_generations(int generations) {
  std::string s = "Number of Generations: ";
  s += std::to_string(generations);
  DrawText(s.c_str(), 10, 10, 20, BLACK); 
}

World::World(int cell_size) {
  this->cell_size = cell_size;  
  
  for (int x = 0; x < WIDTH; x += cell_size) {
    for (int y = 0; y < HEIGHT; y += cell_size) {
      this->create_cell(x, y);
    }
  }
}

void World::update() {
  this->process_input();
  this->draw_cells();
  this->draw_grid_lines();
  this->commit_alive_states();

  draw_num_generations(this->generations);

  if (this->running) {
    this->generations += 1;
  }

  if (this->step) {
    this->step = false;
    this->running = false;
  }
}

void World::commit_alive_states() {
  for (auto c: this->cells) {
    c.second->commit_alive_state();
  }
}

void World::process_input() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    int mouse_x = round_to_nearest_cell(GetMouseX(), this->cell_size);
    int mouse_y = round_to_nearest_cell(GetMouseY(), this->cell_size); 

    std::array<int, 2> position = { mouse_x, mouse_y };
    bool cell_exists = this->cells.contains(position);

    if (cell_exists) {
      auto* cell = this->cells[position];
      cell->is_alive = !cell->is_alive;
    }
  }

  switch(GetKeyPressed()) {
    case KEY_SPACE:
      this->running = !this->running;
      break;
    case KEY_RIGHT:
      std::cout << "STEP" << std::endl;
      this->step = true;
      this->running = true;
      break;
  }
}

void World::draw_cells() {
  auto cell_size = this->cell_size;
  for (auto kv: this->cells) {
    auto* cell = kv.second;
    auto location = kv.first;
    auto x = cell->x;
    auto y = cell->y;

    if (cell->is_alive) {
      DrawRectangle(x, y, cell_size, cell_size, RED);
    }

    if (this->running) {
      auto neighbor_states = this->get_neighbor_states(cell);
      cell->update(neighbor_states);
    } 
  }  
}

NeighborStates World::get_neighbor_states(Cell* cell) {
  NeighborStates ns;

  ns.top_left = false;
  ns.top = false;
  ns.top_right = false;
  ns.left = false;
  ns.right = false;
  ns.bottom_left = false;
  ns.bottom_right = false;
  ns.bottom = false;

  auto cell_size = this->cell_size; 
  auto cell_x = cell->x;
  auto cell_y = cell->y;

  std::array<int, 2> top_left = { cell_x - cell_size, cell_y - cell_size };
  std::array<int, 2> top = { cell_x, cell_y - cell_size };
  std::array<int, 2> top_right = { cell_x + cell_size, cell_y - cell_size };
  std::array<int, 2> left = { cell_x - cell_size, cell_y };
  std::array<int, 2> right = { cell_x + cell_size, cell_y };
  std::array<int, 2> bottom_right = { cell_x + cell_size, cell_y + cell_size };
  std::array<int, 2> bottom = { cell_x, cell_y + cell_size};
  std::array<int, 2> bottom_left = { cell_x - cell_size, cell_y + cell_size };

  bool tl_exists = this->cells.contains(top_left);
  bool t_exists = this->cells.contains(top);
  bool tr_exists = this->cells.contains(top_right);
  bool l_exists = this->cells.contains(left);
  bool r_exists = this->cells.contains(right);
  bool br_exists = this->cells.contains(bottom_right);
  bool b_exists = this->cells.contains(bottom);
  bool bl_exists = this->cells.contains(bottom_left);

  if (tl_exists) { ns.top_left = this->cells[top_left]->is_alive; }
  if (t_exists) { ns.top = this->cells[top]->is_alive; }
  if (tr_exists) { ns.top_right = this->cells[top_right]->is_alive; }
  if (r_exists) { ns.right = this->cells[right]->is_alive; }
  if (l_exists) { ns.left = this->cells[left]->is_alive; }
  if (bl_exists) { ns.bottom_left = this->cells[bottom_left]->is_alive; }
  if (b_exists) { ns.bottom = this->cells[bottom]->is_alive; }
  if (br_exists) { ns.bottom_right = this->cells[bottom_right]->is_alive; }

  return ns;
}

void World::create_cell(int x, int y) {
  Cell* cell = new Cell(x, y);
  std::array<int, 2> location = { x, y };
  auto pair = std::pair<std::array<int, 2>, Cell*>(location, cell);
  this->cells.insert(pair);
}

void World::draw_grid_lines() {
  for (int x = 0; x < WIDTH; x += this->cell_size) {
    DrawLine(x, 0, x, HEIGHT, BLACK); 
  }

  for (int y = 0; y < HEIGHT; y += this->cell_size) {
    DrawLine(0, y, WIDTH, y, BLACK);
  }
}
