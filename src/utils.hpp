#ifndef H_UTILS
#define H_UTILS

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <memory>
#include "../include/raylib.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int CELL_SIZE = 20;
const int FPS = 60;

int round_to_nearest_cell(int x, int cell_size);

#endif
