#ifndef  __COLORS__
#define __COLORS__


#include "characters.h"

typedef struct{
  int r;
  int g;
  int b;
  int a;//just to align the memroy
} Color;

#ifndef __CANVAS__
  #include "canvas.h"
#endif


typedef struct {
  Color fg;
  Color bg;
  CodeMap c;
} FBColor;


#define COLOR_FMT "\x1b[%d;2;%d;%d;%dm%s"
#define COLOR(c) c.r, c.g, c.b
#define RESET_COLOR "\x1b[0m"


FBColor color_merge(Color c1, Color c2);
Color color_mul(Color c,float value);
Color color_add(Color c1,Color c2);
Color color_merge_bilinear(Color c1,Color c2,float amount);

static const Color RED = {.r = 255, .g = 100, .b = 100};
static const Color GREEN ={ .r = 100,.g = 255, .b = 100};
static const Color BLUE = { .r = 100, .g = 100,.b = 255};
static const Color YELLOW ={.r = 255, .g = 255, .b = 100};
static const Color BLACK = {.r = 0, .g = 0,.b = 0 };
static const Color WHITE = {.r = 250, .g = 250,.b = 255};


#endif