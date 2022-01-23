#include "world.hpp"
#include "utils.hpp"

int main() {
  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(60);

  World world(20);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    world.update();
    EndDrawing(); 
  }
}
