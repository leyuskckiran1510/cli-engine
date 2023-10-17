#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ansi_codes.h"
#include "canvas.h"
#include "cli-engine.h"
#include "colors.h"
#include "utils/util.h"

int SWAP = 0;

#define min(x,y) x<y?x:y

void canvas_draw(Canvas *canvas) {
  vec2i window = get_terminal_size();

  float aspect_ratio = (float)canvas->height / (float)canvas->width;
  float scaleX =(float)window.x / (float)canvas->width;
  float scaleY = (float) window.y /(float)canvas->height;
  float scale = min(scaleX,scaleY); 
  // int new_width = window.x;
  // int new_height = window.y*aspect_ratio;

  int new_width = canvas->width*scale;
  int new_height = canvas->height*scale;
  
  int top_padding = (window.y-new_height)/2;
  int left_padding = (window.x-new_width)/2;
  // printf("\npadding_top  =| %d |\t new_height = | %d | \t window.y = | %d | \n",top_padding,new_height,window.y);
  // printf("\npadding_left =| %d |\t new_width  = | %d | \t window.x = | %d | \n",left_padding,new_width,window.x);
  // getchar();
  // // getchar();
  // exit(0);


  int pixel_size = strlen(ANSI_FGBG_RGB_FMT);
  int header_length = strlen(ANSI_BUFFER1 ANSI_CURSOR(1, 1) ANSI_CURSOR_N);
  // char *pixel_buffer =
  //     malloc((new_height * new_width * pixel_size) + header_length+top_padding);

  char *pixel_buffer =
      malloc((canvas->height * canvas->width * pixel_size) + header_length);



  int buffer_index = 0;

  


  if (SWAP) {
    strcpy(pixel_buffer, ANSI_BUFFER1 ANSI_CURSOR(1, 1) ANSI_CURSOR_N);
  } else {
    strcpy(pixel_buffer, ANSI_BUFFER2 ANSI_CURSOR(1, 1) ANSI_CURSOR_N);
  }
  buffer_index += header_length;
  for(int i=0;i<top_padding;i++){
    *(pixel_buffer+i) = '0';
  }
  buffer_index+=top_padding;
  // char utf8[4] ="\0\0\0\0";
  char utf8[4] ="▄" ;//"\0\0\0\0";

  for (int i = 0; i < canvas->height-1; i += 2) {
    for (int j = 0; j < canvas->width; j++) {

      Color c1 = canvas_get(canvas,j,i+1);
      Color c2 = canvas_get(canvas,j,i+1);

      FBColor c = color_merge(c1, c2);
      // (void)unsigned_to_unicode(c.c.u, utf8);
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

Color canvas_get(Canvas *canvas,int x,int y){
  Color color={0};
  if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height) {
     color=canvas->surface[y * canvas->width + x];
  }
  return color;
}

void canvas_fill(Canvas *canvas, Color with) {
  for (int i = 0; i < canvas->height; i++)
    for (int j = 0; j < canvas->width; j++)
      canvas->surface[i * canvas->width + j] = with;
}



void canvas_clear(Canvas *canvas){
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
