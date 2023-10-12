#include "canvas.h"
#include "cli-engine.h"
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
  rectangle(c, 10, 10, 50, 50, BLUE, OUTLINE);
  line(c, 10, 10, 60, 60, YELLOW);
  line(c, 60, 10, 10, 60, YELLOW);
  rectangle(c, 10, 10, 40, 30, RED, FILLED);
  circle(c, 30 + c->width / 2, 0 + c->height / 2, 21, RED, OUTLINE);
  circle(c, 30 + c->width / 2, 0 + c->height / 2, 20, YELLOW, FILLED);
  circle(c, 60 + c->width / 2, 30 + c->height / 2,10, YELLOW, STROKED);
  rectangle(c, 60, 30, 13, 13, BLUE, STROKED);
}

void bouncingball(Canvas *canvas, vec_circle ball) {
  circle(canvas, ball.x, ball.y, ball.r, RED, STROKED);
}

void free_all(Canvas *c) {
  free(c->surface);
  free(c);
  c = NULL;
}

#define FPS 60

int main() {
  clear_screen();
  Canvas *c = InitWindow(127, 80, "HELLO TTY");
  vec_circle balls[5] = {{.x = 100.f, .y = 1, .r = 10},
                         {.x = 30, .y = 0, .r = 5},
                         {.x = 40, .y = 13, .r = 6},
                         {.x = 50, .y = 26, .r = 7},
                         {.x = 60, .y = 39, .r = 8},
                       };
  vec2f velocs[5] = {{1.f, 0.f},
                     {2.f, 2.f},
                     {2.f, 2.f},
                     {2.f, 2.f},
                     {2.f, 2.f},
                   };
  float gravity = 300;
  char key;
  while (1) {
    key = keypress();
    switch (key) {
    case KEY_q:
    case KEY_Q: {
      free_all(c);
      copy_to_clipboard("Thank you for using cli-engine "); // easter egg
      return 0;
    }
    case KEY_a:
    case KEY_A: {
      printf("Pressed A/a");
      usleep(5000);
      break;
    }
    default:
      break;
    }

    // for (size_t i = 0; i < sizeof(balls) / sizeof(vec_circle); i++) {
    //   for (size_t j = i; j < sizeof(balls) / sizeof(vec_circle); j++) {
    //     if (i == j)
    //       continue;
    //     if ((balls[i].x + balls[i].r >= balls[j].x - balls[j].r &&
    //          balls[i].x + balls[i].r <= balls[j].x + balls[j].r) &&
    //       (balls[i].y + balls[i].r >= balls[j].y - balls[j].r &&
    //          balls[i].y + balls[i].r <= balls[j].y + balls[j].r)) {
    //       velocs[i].x *= -1;
    //       velocs[j].x *= -1;
    //       velocs[i].y *= -1;
    //       velocs[j].y *= -1;
    //     }
    //   }
    //   if (balls[i].x - balls[i].r <= 0 || balls[i].x >= c->width - balls[i].r) {
    //     velocs[i].x *= -0.9;
    //   }

    //   if (balls[i].y >= c->height - balls[i].r) {
    //     balls[i].y = c->height - balls[i].r;
    //     velocs[i].y *= -0.7;
    //   }
    //   balls[i].x += velocs[i].x;
    //   balls[i].y += velocs[i].y * (1.0f / 30);

    //   velocs[i].y += (gravity * (1.0f / 30));
    //   bouncingball(c, balls[i]);
    // }
    shapes_test(c);
    c->draw(c);
    c->fill(c, BLACK);
    usleep(1000 * 1000 / FPS);
  }
  reset_all();
  return 0;
}
