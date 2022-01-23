#ifndef H_UTILS
#define H_UTILS

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include "../include/raylib.h"

#define WIDTH 800
#define HEIGHT 600
#define CELL_SIZE 20
#define FPS 60
#define TITLE "Game of Life"

int round_to_nearest_cell(int x, int cell_size);

#endif
