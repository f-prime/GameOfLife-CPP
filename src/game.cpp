#include "world.hpp"
#include "utils.hpp"

const char* TITLE = "Game of Life";

int main() {
  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(FPS);

  World world(CELL_SIZE);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    world.update();
    EndDrawing(); 
  }
}
