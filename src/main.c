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

/*
f(x,y,z)=1/sqrt((x-x0)^2+(y-y_0)^2+(z-z_0)^2)
f(r) = (1/r^2)^2

let xdif = x - blobs[i].x;
        let ydif = y - blobs[i].y;
        let d = sqrt((xdif * xdif) + (ydif * ydif));
*/

typedef struct{
  int x,y;
}Vec2;

float fl(int r){
  return (1.0/r*r)*(1.0/r*r);
}

float f(Vec2 v1,Vec2 v2){
  float x = v1.x-v2.x;
  float y= v1.y-v2.y;
  return 1.0/sqrt(x*x+y*y);
}

void metaball(Canvas *c,Vec2 ball1,Vec2 ball2){
  for(int y=0;y<c->height;y++){
    for(int x=0;x<c->width;x++){
      // printf("%f\n",f(ball1,(Vec2){.x=x,.y=y})+f(ball2,(Vec2){.x=x,.y=y}));
      if(f(ball1,(Vec2){.x=x,.y=y})+f(ball2,(Vec2){.x=x,.y=y})<0.02){
        c->place(c,x,y,RED);
      }
    }
  }
}

void shapes_test(Canvas *c){
  rectangle(c, 10, 10, 50, 50, BLUE, OUTLINE);
  line(c, 10, 10, 60, 60, YELLOW);
  line(c, 60, 10, 10, 60, YELLOW);
  rectangle(c, 10, 10, 40, 30, RED, FILLED);
  circle(c, 30+c->width/2, 0+c->height/2, 21, RED, OUTLINE);
  circle(c, 30+c->width/2, 0+c->height/2, 20, YELLOW, FILLED);
}



int main() {
  Canvas *c = canvas_init(125, 75);
  // shapes_test(c);
  Vec2 ball1 = {.x=10,.y=20};
  Vec2 ball2 = {.x=30,.y=30};
  int counter=0;
  while (1) {
    system("clear");
    metaball(c,ball1,ball2);
    c->draw(c);
    counter++;
    ball1.x +=sin(counter);
    ball1.y +=cos(counter);
  }
  // printf("%ld\n",sizeof(int));
  return 0;
}
