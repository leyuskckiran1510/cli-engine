#ifndef __SHAPES__
#define __SHAPES__

#ifndef __CLI_ENGINE__
    #include "./../cli-engine.h"
#endif

typedef enum {
  OUTLINE = 1,                // 01
  FILLED = 2,                 // 10
  STROKED = OUTLINE | FILLED, // 11 or 3
} SHAPE_TYPE;

void rectangle(Canvas *c, int x, int y, int width, int height, Color color,
               SHAPE_TYPE type);
void line(Canvas *c, int sx, int sy, int ex, int ey, Color color);
void circle_variance(Canvas *c, int x, int y, int xorg, int yorg, Color color);
void circle_outline(Canvas *c, int cx, int cy, int r, Color color);
void circle(Canvas *c, int cx, int cy, int r, Color color, SHAPE_TYPE type);

#endif