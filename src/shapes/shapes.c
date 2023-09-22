
#include "shapes.h"

#define square(x) ((x)*(x))


void int_swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
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

void circle_outline(Canvas *c, int cx, int cy, int r, Color color){
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
    circle_outline(c, cx, cy, r, color);
  }
}