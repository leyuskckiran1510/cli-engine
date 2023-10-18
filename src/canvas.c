#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ansi_codes.h"
#include "canvas.h"
#include "cli-engine.h"
#include "colors.h"
#include "utils/util.h"

int SWAP = 0;

#define min(x, y) x < y ? x : y

void canvas_draw(Canvas *canvas) {
  vec2i window = get_terminal_size();
  int new_height = 0, new_width = 0;
  float h_m_c = 2.0; // height_merge_count
  float scaleX = (float)window.x / (float)canvas->width;
  float scaleY = ((float)window.y * h_m_c) / ((float)(canvas->height));
  if (scaleX > scaleY) {
    new_width = canvas->width * (scaleY);
    new_height = window.y * h_m_c;
  } else {
    new_width = window.x;
    new_height = canvas->height * (scaleX);
  }
  int top_padding = (window.y * h_m_c > new_height)
                        ? (window.y * h_m_c - new_height) / (h_m_c * 2)
                        : 0;
  int left_padding = (window.x > new_width) ? (window.x - new_width) / 2 : 0;
  int pixel_size = strlen(ANSI_FGBG_RGB_FMT);
  char *HEADER[] = {ANSI_BUFFER1 ANSI_CURSOR(1, 1) ANSI_CURSOR_N ANSI_CLR "\0",
                    ANSI_BUFFER2 ANSI_CURSOR(1, 1) ANSI_CURSOR_N ANSI_CLR "\0"};
  int header_length = strlen(HEADER[0]);
  char *pixel_buffer =
      malloc(((new_height / h_m_c) * new_width * pixel_size) + header_length);
  int buffer_index = 0;
  if (SWAP) {
    strcpy(pixel_buffer, HEADER[0]);
  } else {
    strcpy(pixel_buffer, HEADER[1]);
  }
  buffer_index += header_length;

  // char utf8[4] ="\0\0\0\0";
  char utf8[4] = "▄";
  /*-----Top Padding-----*/
  for (int i = 0; i < top_padding; i++) {
    pixel_buffer[buffer_index++] = '\n';
  }
  for (int i = 0; i < new_height; i += h_m_c) {
    /*---- Left Padding-----*/
    for (int i = 0; i < left_padding; i++) {
      pixel_buffer[buffer_index++] = ' ';
    }
    for (int j = 0; j < new_width; j++) {
      Color c1 = canvas_get(canvas, j, i);
      Color c2 = canvas_get(canvas, j, i + 1);
      FBColor c = color_merge(c1, c2);
      buffer_index +=
          snprintf(&pixel_buffer[buffer_index], pixel_size,
                   ANSI_FGBG_RGB_FMT "%s", COLOR(c.fg), COLOR(c.bg), utf8);
    }
    strcpy(&pixel_buffer[buffer_index], RESET_COLOR);
    buffer_index += 4;
    pixel_buffer[buffer_index++] = '\n';
  }

  printf("%s", pixel_buffer);
  printf(ANSI_CURSOR(1, 1) ANSI_CURSOR_Y);
  free(pixel_buffer);
  SWAP ^= 1;
}

void canvas_place(Canvas *canvas, int x, int y, Color color) {
  if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height) {
    canvas->surface[y * canvas->width + x] = color;
  }
}

Color canvas_get(Canvas *canvas, int x, int y) {
  Color color = {0};
  if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height) {
    color = canvas->surface[y * canvas->width + x];
  }
  return color;
}

void canvas_fill(Canvas *canvas, Color with) {
  for (int i = 0; i < canvas->height; i++)
    for (int j = 0; j < canvas->width; j++)
      canvas->surface[i * canvas->width + j] = with;
}

void canvas_clear(Canvas *canvas) {
  size_t canvasSize = (canvas->width) * (canvas->height) * sizeof(Color);
  memset(canvas->surface, 0, canvasSize);
}

Canvas *canvas_init(int width, int height) {
  Color BLACK = (Color){.b = 0, .g = 0, .r = 0};
  Canvas *c = malloc(sizeof(Canvas));
  c->width = width;
  c->height = height;
  c->draw = &canvas_draw;
  c->fill = &canvas_fill;
  c->surface = malloc((sizeof(Color)) * width * height);
  c->place = &canvas_place;
  c->fill(c, BLACK);
  c->clear = canvas_clear;
  return c;
}
