#include "colors.h"


FBColor color_merge(Color c1, Color c2){
  FBColor c = {.fg = c2, .bg = c1, .c = normal_pallete[98]};
  return c;
}


Color color_mul(Color c,float value){
  int max = 255;
  c.r =(c.r *value)<max?(c.r *value):max;
  c.g =(c.g *value)<max?(c.g *value):max;
  c.b =(c.b *value)<max?(c.b *value):max;
  c.a =(c.a *value)<max?(c.a *value):max;
  return c;
}
Color color_add(Color c1,Color c2){
  int max = 255;
  c1.r =(c1.r +c2.r)<max?(c1.r +c2.r):max;
  c1.g =(c1.g +c2.g)<max?(c1.g +c2.g):max;
  c1.b =(c1.b +c2.b)<max?(c1.b +c2.b):max;
  c1.a =(c1.a +c2.a)<max?(c1.a +c2.a):max;
  return c1;
}


FBColor color_merge_bilinear(Canvas* canvas,int x,int y,float amount){
  (void)amount;
  Color c1 = canvas_get(canvas, x, y);
  Color c2 = canvas_get(canvas, x, y + 1);
  FBColor c = color_merge(c1, c2);
  return c;
}