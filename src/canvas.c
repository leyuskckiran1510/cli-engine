#include <stdlib.h>
#include <stdio.h>
#include "colors.h"

#include "canvas.h"
#include "unicode/decode.h"




void canvas_draw(Canvas *canvas) {
  /*
    For now making sure that we dont touch the unallocated memory when height is odd
  */
  int padding = canvas->height%2;
  char utf8[4];
  for (int i = 0; i < canvas->height-padding; i += 2) {
    for (int j = 0; j < canvas->width; j++) {
      Color c1 = canvas->surface[(i + 1 * 0) * canvas->width + j];
      Color c2 = canvas->surface[(i + 1 * 1) * canvas->width + j];
      FBColor c = color_merge(c1, c2);
      (void)unsigned_to_unicode(c.c.u, utf8);
      printf("\033[38;2;%d;%d;%d;48;2;%d;%d;%dm%s", COLOR(c.fg), COLOR(c.bg),
             utf8);
    }
    printf("%s\n", RESET_COLOR);
  }
}


void canvas_place(Canvas *canvas, int x, int y, Color color) {
  if (x>=0 && x<canvas->width && y>=0 && y<canvas->height){
      canvas->surface[y * canvas->width + x] = color;
  }
}
void canvas_fill(Canvas *canvas, Color with) {
  for (int i = 0; i < canvas->height; i++)
    for (int j = 0; j < canvas->width; j++)
      canvas->place(canvas,i,j,with);
}

Canvas *canvas_init(int width, int height) {
  Color BLACK = (Color){.b = 0, .g = 0, .r = 0};
  Canvas *c = malloc(sizeof(Canvas));
  c->width = width;
  c->height = height;
  c->draw = &canvas_draw;
  c->fill = &canvas_fill;
  c->surface = malloc((sizeof(Color)) * width * height);
  c->place = &canvas_place;
  c->fill(c, BLACK);
  return c;
}
