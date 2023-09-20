#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "characters.h"
#include "unicode/decode.h"
#include "shapes/shapes.h"
#include "canvas.h"
#include "colors.h"



int main() {
  Canvas *c = canvas_init(125, 75);
  rectangle(c, 10, 10, 50, 50, BLUE, OUTLINE);
  line(c, 10, 10, 60, 60, YELLOW);
  line(c, 60, 10, 10, 60, YELLOW);
  rectangle(c, 10, 10, 40, 30, RED, FILLED);
  circle(c, 30+c->width/2, 0+c->height/2, 21, RED, OUTLINE);
  circle(c, 30+c->width/2, 0+c->height/2, 20, YELLOW, FILLED);
  c->draw(c);
  // printf("%ld\n",sizeof(int));
  return 0;
}
