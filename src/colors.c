#include "colors.h"


FBColor color_merge(Color c1, Color c2){
  FBColor c = {.fg = c2, .bg = c1, .c = normal_pallete[98]};
  return c;
}


Color color_mul(Color c,float value){
  int max = 255;
  if(value<0)
    return (Color){0};
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


Color color_merge_bilinear(Color c1,Color c2,float amount){
  c1.r = (1 - amount) * c1.r + amount * c2.r;
  c1.g = (1 - amount) * c1.g + amount * c2.g;
  c1.b = (1 - amount) * c1.b + amount * c2.b;
  return c1;
}