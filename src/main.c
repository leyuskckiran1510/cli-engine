#include "canvas.h"
#include "cli-engine.h"
#include "colors.h"
#include "event.h"
#include "shapes/shapes.h"
#include "utils/util.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  float x, y;
  float r;
} vec_circle;

float fl(int r) { return (1.0 / r * r) * (1.0 / r * r); }

float f(vec_circle v1, vec_circle v2) {
  float x = v1.x - v2.x;
  float y = v1.y - v2.y;
  return 1.0 / sqrt(x * x + y * y);
}

void metaball(Canvas *c, vec_circle ball1, vec_circle ball2) {
  for (int y = 0; y < c->height; y++) {
    for (int x = 0; x < c->width; x++) {
      // printf("%f\n",f(ball1,(Vec2){.x=x,.y=y})+f(ball2,(Vec2){.x=x,.y=y}));
      if (f(ball1, (vec_circle){.x = x, .y = y}) +
              f(ball2, (vec_circle){.x = x, .y = y}) <
          0.02) {
        c->place(c, x, y, RED);
      }
    }
  }
}
void shapes_test(Canvas *c) {
  line(c, 10, 10, 60, 60, YELLOW);
  line(c, 60, 10, 10, 60, YELLOW);
  line(c, 0, 0, 100, 100, BLUE);
  line(c, 0, 0, c->width, 0, (Color){.r = 10, .b = 20, .g = 0});
  line(c, 0, 0, 0, c->height, (Color){.r = 17, .b = 39, .g = 27});
  line(c, 0, 0, c->width, c->height, (Color){.r = 24, .b = 58, .g = 54});
  line(c, c->width, 0, 0, c->height, (Color){.r = 31, .b = 77, .g = 81});
  line(c, c->width, c->height - 1, 0, c->height - 1,
       (Color){.r = 38, .b = 96, .g = 108});
  line(c, c->width - 1, c->height - 1, c->width - 1, 0,
       (Color){.r = 45, .b = 115, .g = 135});
  

  circle(c, 0, 0, 10, YELLOW, STROKED);
  circle(c,c->width, 0 + c->height / 2, 21, RED, OUTLINE);
  circle(c, 30 + c->width / 2, 0 + c->height / 2, 20, YELLOW, FILLED);
  circle(c, 60 + c->width / 2, 30 + c->height / 2, 10, YELLOW, STROKED);


  rectangle(c, 10, 10, 50, 50, BLUE, OUTLINE);
  rectangle(c, 10, 10, 40, 30, GREEN, FILLED);
  rectangle(c, 60, 30, 13, 13, BLUE, STROKED);
}

void bouncingball(Canvas *canvas, vec_circle ball) {
  circle(canvas, ball.x, ball.y, ball.r, RED, OUTLINE);
}

void free_all(Canvas *c) {
  free(c->surface);
  free(c);
  c = NULL;
}

#define FPS 120

int main() {
  clear_screen();
  Canvas *c = InitWindow(200,100, "HELLO TTY");
  vec_circle balls[5] = {
      {.x = 100.f, .y = 1, .r = 10}, {.x = 30, .y = 0, .r = 5},
      {.x = 40, .y = 13, .r = 6},    {.x = 50, .y = 56, .r = 7},
      {.x = 60, .y = 39, .r = 8},
  };
  vec2f velocs[5] = {
      {1.f, 0.f}, {2.f, 2.f}, {2.f, 2.f}, {2.f, 2.f}, {2.f, 2.f},
  };
  float gravity = 300;
  char key;
  int counter=0;
  int pause=0;
  while (1) {
    key = keypress();
    switch (key) {
    case KEY_q:
    case KEY_Q: {
      free_all(c);
      copy_to_clipboard(" Thank you for using cli-engine "); // easter egg
      return 0;
    }
    case KEY_a:
    case KEY_A: {
      printf("Pressed A/a");
      usleep(5000);
      break;
    }
    case KEY_SPACE:{
      pause^=1;
      break;
    }
    default:
      break;
    }
    if(pause)continue;
#ifdef __ANIMATION__
    for (size_t i = 0; i < sizeof(balls) / sizeof(vec_circle); i++) {
      for (size_t j = i; j < sizeof(balls) / sizeof(vec_circle); j++) {
        if (i == j)
          continue;
        if ((balls[i].x + balls[i].r >= balls[j].x - balls[j].r &&
             balls[i].x + balls[i].r <= balls[j].x + balls[j].r) &&
            (balls[i].y + balls[i].r >= balls[j].y - balls[j].r &&
             balls[i].y + balls[i].r <= balls[j].y + balls[j].r)) {
          velocs[i].x *= -1;
          // balls[i].x += velocs[i].x*balls[j].r; 
          // balls[i].y += velocs[i].y*balls[j].r; 
          velocs[j].x *= -1;
          velocs[i].y *= -1;
          velocs[j].y *= -1;
        }
      }
      if (balls[i].x - balls[i].r <= 0 || balls[i].x >= c->width - balls[i].r) {
        velocs[i].x *= -0.9;
      }

      if (balls[i].y >= c->height - balls[i].r) {
        balls[i].y = c->height - balls[i].r;
        velocs[i].y *= -0.7;
      }
      balls[i].x += velocs[i].x;
      balls[i].y += velocs[i].y * (1.0f / FPS);

      velocs[i].y += (gravity * (1.0f / FPS));
      bouncingball(c, balls[i]);
    }
#else
    shapes_test(c);
#endif
    c->draw(c);
    c->clear(c);
    // c->fill(c, BLACK);
    // usleep(1000 * 1000 / FPS);
  }
  free_all(c);
  reset_all();
  return 0;
}
