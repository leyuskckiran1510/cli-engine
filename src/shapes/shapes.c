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
        canvas_place(c,i,j,color);
      }
    }
  }
  if(type&OUTLINE){
    for (int i = x; i < x + width; i++) {
       canvas_place(c,i,y,color);
    }
    for (int i = x; i < x + width; i++) {
       canvas_place(c,i,y+height,color);
    }
    for (int i = y; i < y + height; i++) {
       canvas_place(c,x,i,color);
    }
    for (int i = y; i <= y + height; i++) {
       canvas_place(c,x+width,i,color);
    }
  }
  
}

void line(Canvas *c,int x,int y,int x2, int y2, Color color) {
    int w = x2 - x ;
    int h = y2 - y ;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
    if (w<0) dx1 = -1 ; else if (w>0) dx1 = 1 ;
    if (h<0) dy1 = -1 ; else if (h>0) dy1 = 1 ;
    if (w<0) dx2 = -1 ; else if (w>0) dx2 = 1 ;
    int longest = abs(w) ;
    int shortest = abs(h) ;
    if (!(longest>shortest)) {
        longest = abs(h) ;
        shortest = abs(w) ;
        if (h<0) dy2 = -1 ; else if (h>0) dy2 = 1 ;
        dx2 = 0 ;            
    }
    int numerator = longest >> 1 ;
    for (int i=0;i<=longest;i++) {
        canvas_place(c,x,y,color);
        numerator += shortest ;
        if (!(numerator<longest)) {
            numerator -= longest ;
            x += dx1 ;
            y += dy1 ;
        } else {
            x += dx2 ;
            y += dy2 ;
        }
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