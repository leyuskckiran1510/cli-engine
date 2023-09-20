#ifndef  __COLORS__
#define __COLORS__

#include "characters.h"

typedef struct{
  int r;
  int g;
  int b;
  int padding;//just to align the memroy
} Color;

typedef struct {
  Color fg;
  Color bg;
  CodeMap c;
} FBColor;


#define COLOR_FMT "\x1b[%d;2;%d;%d;%dm%s"
#define COLOR(c) c.r, c.g, c.b
#define RESET_COLOR "\x1b[0m"


FBColor color_merge(Color c1, Color c2);

static const Color RED = (Color){.r = 255, .g = 100, .b = 100};
static const Color GREEN = (Color){ .r = 100,.g = 255, .b = 100};
static const Color BLUE = (Color){ .r = 100, .g = 100,.b = 255};
static const Color YELLOW = (Color){.r = 255, .g = 255, .b = 100};
static const Color BLACK = (Color){.r = 0, .g = 0,.b = 0 };


#endif