#include "canvas.h"
#include "cli-engine.h"
#include "event.h"
#include "utils/util.h"
#include <stdlib.h>


typedef struct{
  int x,y;
}vec2;

float fl(int r){
  return (1.0/r*r)*(1.0/r*r);
}

float f(vec2 v1,vec2 v2){
  float x = v1.x-v2.x;
  float y= v1.y-v2.y;
  return 1.0/sqrt(x*x+y*y);
}

void metaball(Canvas *c,vec2 ball1,vec2 ball2){
  for(int y=0;y<c->height;y++){
    for(int x=0;x<c->width;x++){
      // printf("%f\n",f(ball1,(Vec2){.x=x,.y=y})+f(ball2,(Vec2){.x=x,.y=y}));
      if(f(ball1,(vec2){.x=x,.y=y})+f(ball2,(vec2){.x=x,.y=y})<0.02){
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

void bouncingball(Canvas *canvas,vec2 ball){
  canvas->fill(canvas,BLACK);
  circle(canvas,ball.x,ball.y,10,RED,FILLED);

}


void free_all(Canvas *c){
  free(c->surface);
  free(c);
  c=NULL;
}


int main() {
  // clear_screen();
  Canvas *c = InitWindow(127,80,"HELLOW WORLDDD ;D");
  shapes_test(c);
  vec2 ball1 = {.x=10,.y=20};
  // vec2 ball2 = {.x=30,.y=30};
  int dx=1,dy=1;
  int counter=0;
  char key;
  while (1) {
    key=keypress();
    switch (key) {
      case KEY_q:
      case KEY_Q:{
        free_all(c);
        copy_to_clipboard("Thank you for using cli-engine ");
        return 0;
    }
  }
    bouncingball(c,ball1);
    c->draw(c);
    counter++;
    if(ball1.x<=0 || ball1.x>=c->width)
      dx*=-1;
    if(ball1.y<=0 || ball1.y>=c->height)
      dy*=-1;
    ball1.x+=dx;
    ball1.y+=dy;
      }
  return 0;
}
