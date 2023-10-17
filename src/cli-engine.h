#ifndef __CLI_ENGINE__
#define __CLI_ENGINE__
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "canvas.h"
#include "characters.h"
#include "utils/util.h"
#ifndef __SHAPES__
#include "shapes/shapes.h"
#endif
void clear_screen();
void reset_all();
Canvas* InitWindow(int width, int height, const char *title);  // Initialize window and OpenGL context

#endif
