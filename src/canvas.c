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
  for (int _ = 0; _ < top_padding; _++) {
    pixel_buffer[buffer_index++] = '\n';
  }

  for (int row = 0; row < new_height; row += h_m_c) {

    /*---- Left Padding-----*/
    for (int _ = 0; _ < left_padding; _++) {
      pixel_buffer[buffer_index++] = ' ';
    }

    for (int col = 0; col < new_width; col++) {
      float x_l = floor(scaleX * col);
      float x_h = ceil(scaleX * col);
      float y1_l = floor(scaleY * row);
      float y1_h = ceil(scaleY * row);

      float y2_l = floor(scaleY * (row+1));
      float y2_h = ceil(scaleY * (row+1));

      float x_weight = (scaleX * col) - x_l;
      float y1_weight = (scaleY * col) - y1_l;
      float y2_weight = (scaleY * col) - y2_l;


      Color c1_arr_temp[4] = {
          canvas_get(canvas, x_l, y1_l),
          canvas_get(canvas, x_h, y1_l),
          canvas_get(canvas, x_l, y1_h),
          canvas_get(canvas, x_h, y1_h),
      };
      Color c1_arr[4] = {color_mul(c1_arr_temp[0], (1 - x_weight) * (1 - y1_weight)),
                         color_mul(c1_arr_temp[1], (x_weight) * (1 - y1_weight)),
                         color_mul(c1_arr_temp[2], (1 - x_weight) * (y1_weight)),
                         color_mul(c1_arr_temp[3], (x_weight) * (y1_weight))};
      Color c1 = color_add(c1_arr[0],c1_arr[1]);
      c1 = color_add(c1,c1_arr[2]);
      c1 = color_add(c1,c1_arr[3]);

       Color c2_arr_temp[4] = {
          canvas_get(canvas, x_l, y2_l),
          canvas_get(canvas, x_h, y2_l),
          canvas_get(canvas, x_l, y2_h),
          canvas_get(canvas, x_h, y2_h),
      };
      Color c2_arr[4] = {color_mul(c2_arr_temp[0], (1 - x_weight) * (1 - y2_weight)),
                         color_mul(c2_arr_temp[1], (x_weight) * (1 - y2_weight)),
                         color_mul(c2_arr_temp[2], (1 - x_weight) * (y2_weight)),
                         color_mul(c2_arr_temp[3], (x_weight) * (y2_weight))};
      Color c2 = color_add(c2_arr[0],c2_arr[1]);
      c2 = color_add(c2,c2_arr[2]);
      c2 = color_add(c2,c2_arr[3]);

      // Color c2 = c1;
      FBColor c = color_merge(c1, c2);

      // FBColor c =
      // color_merge_bilinear(canvas,j,i,canvas->width/(float)new_width);
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
