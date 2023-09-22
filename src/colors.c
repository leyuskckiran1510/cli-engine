#ifndef __COLORS__
#include "colors.h"


FBColor color_merge(Color c1, Color c2){
  FBColor c = {.fg = c2, .bg = c1, .c = normal_pallete[98]};
  return c;
}
#endif