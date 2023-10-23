#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ansi_codes.h"
#include "canvas.h"
#include "cli-engine.h"
#include "colors.h"
#include "utils/util.h"

int SWAP = 0;

Color map_coords(Canvas*canvas, int x,int y,int v_width,int v_height,float scale_x,float scale_y){
  Color colr={0};
  float v_x = scale_x*x;
  float v_y = scale_y*y;
  int f_v_x = floor(v_x);
  int f_v_y = floor(v_y);
  float frac_x = v_x - f_v_x;
  float frac_y = v_y - f_v_y;
  colr.r = (1-frac_x)*(1-frac_y)*canvas_get(canvas,f_v_x,f_v_y).r+
           frac_x*(1-frac_y)*canvas_get(canvas,f_v_x+1,f_v_y).r+
           (1-frac_x)*(frac_y)*canvas_get(canvas,f_v_x,f_v_y+1).r+
           frac_x*(frac_y)*canvas_get(canvas,f_v_x+1,f_v_y+1).r;
  colr.g = (1-frac_x)*(1-frac_y)*canvas_get(canvas,f_v_x,f_v_y).g+
           frac_x*(1-frac_y)*canvas_get(canvas,f_v_x+1,f_v_y).g+
           (1-frac_x)*(frac_y)*canvas_get(canvas,f_v_x,f_v_y+1).g+
           frac_x*(frac_y)*canvas_get(canvas,f_v_x+1,f_v_y+1).g;
  colr.b = (1-frac_x)*(1-frac_y)*canvas_get(canvas,f_v_x,f_v_y).b+
           frac_x*(1-frac_y)*canvas_get(canvas,f_v_x+1,f_v_y).b+
           (1-frac_x)*(frac_y)*canvas_get(canvas,f_v_x,f_v_y+1).b+
           frac_x*(frac_y)*canvas_get(canvas,f_v_x+1,f_v_y+1).b;
  return colr;

}

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

  for (int row = 0; row < new_height-h_m_c; row += h_m_c) {

    /*---- Left Padding-----*/
    for (int _ = 0; _ < left_padding; _++) {
      pixel_buffer[buffer_index++] = ' ';
    }

    for (int col = 0; col < new_width; col++) {

      float originalX = col / scaleX;
      float originalY = row / (scaleY);

      Color c1 =  map_coords(canvas,originalX,originalY,new_width,new_height,scaleX,scaleY);
      Color c2 =  map_coords(canvas,originalX,originalY+1,new_width,new_height,scaleX,scaleY);
      
      FBColor c = color_merge(c1,c2);
      buffer_index +=
          snprintf(&pixel_buffer[buffer_index], pixel_size,
                   ANSI_FGBG_RGB_FMT "%s", COLOR(c.fg), COLOR(c.bg), utf8);
    }
    pixel_buffer[buffer_index++] = '\n';
    strcpy(&pixel_buffer[buffer_index], RESET_COLOR);
    buffer_index += 4;
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
