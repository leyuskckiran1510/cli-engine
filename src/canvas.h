#ifndef __CANVAS__
#define __CANVAS__

#include "colors.h"

typedef struct Canvas Canvas;

typedef struct Canvas {
  int width;
  int height;
  Color *surface;
  void (*draw)(Canvas *);
  void (*fill)(Canvas *, Color);
  void (*place)(Canvas *, int, int, Color);
  void (*clear)(Canvas *);
} Canvas;
void canvas_draw(Canvas *canvas);
void canvas_place(Canvas *canvas, int x, int y, Color color);
Color canvas_get(Canvas *canvas,int x,int y);
void canvas_fill(Canvas *canvas, Color with);
void canvas_clear(Canvas *canvas);
Canvas *canvas_init(int width, int height);

#endif