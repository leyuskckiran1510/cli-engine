#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "characters.c"

#define COLOR_FMT "\x1b[%d;2;%d;%d;%dm%s"
#define COLOR(c) c.r, c.g, c.b
#define RESET_COLOR "\x1b[0m"

#define square(x) ((x)*(x))

typedef enum {
  OUTLINE = 1,
  FILLED = 2,
  STROKED = OUTLINE | FILLED, // 3
} SHAPE_TYPE;


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

Color RED = (Color){.r = 255, .g = 100, .b = 100};
Color GREEN = (Color){.g = 255, .r = 100, .b = 100};
Color BLUE = (Color){.b = 255, .g = 100, .r = 100};
Color YELLOW = (Color){.r = 255, .g = 255, .b = 100};
Color BLACK = (Color){.b = 0, .g = 0, .r = 0};

typedef struct Canvas Canvas;

typedef struct Canvas {
  size_t width;
  size_t height;
  Color *surface;
  void (*draw)(Canvas *);
  void (*fill)(Canvas *, Color);
  void (*place)(Canvas *, int, int, Color);
} Canvas;

void int_swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

FBColor color_merge(Color c1, Color c2) {
  FBColor c = {.fg = c2, .bg = c1, .c = normal[98]};
  return c;
}

void draw(Canvas *canvas) {
  /*
    For now making sure that we dont touch the unallocated memory when height is odd
  */
  int padding = canvas->height%2;
  char utf8[3];
  for (int i = 0; i < canvas->height-padding; i += 2) {
    for (int j = 0; j < canvas->width; j++) {
      Color c1 = canvas->surface[(i + 1 * 0) * canvas->width + j];
      Color c2 = canvas->surface[(i + 1 * 1) * canvas->width + j];
      FBColor c = color_merge(c1, c2);
      (void)g_unichar_to_utf8(c.c.u, utf8);
      printf("\033[38;2;%d;%d;%d;48;2;%d;%d;%dm%s", COLOR(c.fg), COLOR(c.bg),
             utf8);
    }
    printf("%s\n", RESET_COLOR);
    // printf("%s%d\n",RESET_COLOR,i);
  }
}


void place(Canvas *canvas, int x, int y, Color color) {
  if (x>=0 && x<canvas->width && y>=0 && y<canvas->height){
      canvas->surface[y * canvas->width + x] = color;
  }
}
void fill(Canvas *canvas, Color with) {
  for (int i = 0; i < canvas->height; i++)
    for (int j = 0; j < canvas->width; j++)
      canvas->place(canvas,i,j,with);
}

Canvas *canvas_init(int width, int height) {
  Canvas *c = malloc(sizeof(Canvas));
  c->width = width;
  c->height = height;
  c->draw = &draw;
  c->fill = &fill;
  c->surface = malloc((sizeof(Color)) * width * height);
  c->place = &place;
  c->fill(c, BLACK);
  return c;
}

void rectangle(Canvas *c, int x, int y, int width, int height, Color color,
               SHAPE_TYPE type) {
  if (type&FILLED) {
    for (int j = y ; j < y + height; j++) {
      for (int i = x ; i < x + width; i++) {
        c->surface[j * c->width + i] = color;
      }
    }
  }
  if(type&OUTLINE){
    for (int i = x; i < x + width; i++) {
      c->surface[y * c->width + i] = color;
    }
    for (int i = x; i < x + width; i++) {
      c->surface[(y + height) * c->width + i] = color;
    }
    for (int i = y; i < y + height; i++) {
      c->surface[i * c->width + x] = color;
    }
    for (int i = y; i <= y + height; i++) {
      c->surface[i * c->width + (x + width)] = color;
    }
  }
  
}

void line(Canvas *c, int sx, int sy, int ex, int ey, Color color) {
  // Besenham line drawing algorithm
  int p = 0, dx = 0, dy = 0, x = 0, y = 0, xinc = 1, yinc = 1, a = 0, b = 0,
      swaped = 0;
  dx = ex - sx;
  dy = ey - sy;
  xinc = 1;
  yinc = 1;
  if (dx < 0) {
    xinc = -1;
    dx = -dx;
  }
  if (dy < 0) {
    yinc = -1;
    dy = -dy;
  }
  x = sx;
  y = sy;
  a = dy;
  b = dx;
  if (dx < dy) {
    swaped = 1;
    int_swap(&a, &b);
    int_swap(&x, &y);
    int_swap(&xinc, &yinc);
  }
  p = 2 * a - b;
  for (int i = 0; i < b; i++) {
    if (swaped) {
      c->place(c, x, y, color);
    } else {
      c->place(c, y, x, color);
    }
    y += yinc * (p >= 0);
    p = p - ((2 * b) * (p >= 0));
    x += xinc;
    p += 2 * a;
  }
  if (swaped) {
    c->place(c, x, y, color);
  } else {
    c->place(c, y, x, color);
  }
}

void circle_variance(Canvas *c, int x, int y, int xorg, int yorg, Color color) {
  c->place(c, x + xorg, y + yorg, color);
  c->place(c, y + xorg, x + yorg, color);
  c->place(c, -x + xorg, y + yorg, color);
  c->place(c, -y + xorg, x + yorg, color);
  c->place(c, y + xorg, -x + yorg, color);
  c->place(c, x + xorg, -y + yorg, color);
  c->place(c, -x + xorg, -y + yorg, color);
  c->place(c, -y + xorg, -x + yorg, color);
}

void circle_outline(Canvas *c, int cx, int cy, int r, Color color, SHAPE_TYPE type){
  // mid-point circle
  int x = 0;
  int y = r;
  int p = 1 - r;
  circle_variance(c, x, y, cx, cy, color);
  for (; x <= y;) {
    x++;
    if (p >= 0) {
      y--;
      p -= 2 * y;
    }
    p += 2 * x + 1;
    circle_variance(c, x, y, cx, cy, color);
  }
}

void circle(Canvas *c, int cx, int cy, int r, Color color, SHAPE_TYPE type) {
  if(type&FILLED){
    for (int j = cy-r; j < cy+r; j++) {
      for (int i = cx-r; i < cx+r; i++) {
        if(square(cy-j)+square(cx-i)<=r*r){
        c->place(c,i,j,color);
        }
      }
    }
  }
  if(type&OUTLINE){
    circle_outline(c, cx, cy, r, color, type);
  }
}

int main() {
  Canvas *c = canvas_init(125, 75);
  rectangle(c, 10, 10, 50, 50, BLUE, OUTLINE);
  line(c, 10, 10, 60, 60, YELLOW);
  line(c, 60, 10, 10, 60, YELLOW);
  rectangle(c, 10, 10, 40, 30, RED, FILLED);
  circle(c, 30+c->width/2, 0+c->height/2, 21, RED, OUTLINE);
  circle(c, 30+c->width/2, 0+c->height/2, 20, YELLOW, FILLED);
  c->draw(c);
  return 0;
}
