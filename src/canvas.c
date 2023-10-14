#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ansi_codes.h"
#include "canvas.h"
#include "cli-engine.h"
#include "colors.h"
#include "utils/util.h"

int SWAP = 0;

void canvas_draw(Canvas *canvas) {

  int padding = canvas->height % 2;
  vec2i w = get_terminal_size();
  if (w.x < 100 && w.y < 100) {
    exit(0);
  }

  int pixel_size = strlen(ANSI_FGBG_RGB_FMT);
  int header_length = strlen(ANSI_BUFFER1 ANSI_CURSOR(1, 1) ANSI_CURSOR_N);

  char *pixel_buffer =
      malloc((canvas->height * canvas->width * pixel_size) + header_length);
  // Filling it zero as 'C' fucking uses NULL terminated string
  // which causes heap-overflow in all functions like printf,snprintf...
  char utf8[4] = "\0\0\0\0"; // just to be sure
  int buffer_index = 0;

  if (SWAP) {
    strcpy(pixel_buffer, ANSI_BUFFER1 ANSI_CURSOR(1, 1) ANSI_CURSOR_N);
  } else {
    strcpy(pixel_buffer, ANSI_BUFFER2 ANSI_CURSOR(1, 1) ANSI_CURSOR_N);
  }
  buffer_index += header_length;

  for (int i = 0; i < canvas->height - padding; i += 2) {
    for (int j = 0; j < canvas->width; j++) {
      Color c1 = canvas->surface[(i + 1 * 0) * canvas->width + j];
      Color c2 = canvas->surface[(i + 1 * 1) * canvas->width + j];
      FBColor c = color_merge(c1, c2);
      (void)unsigned_to_unicode(c.c.u, utf8);
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
void canvas_fill(Canvas *canvas, Color with) {
  for (int i = 0; i < canvas->height; i++)
    for (int j = 0; j < canvas->width; j++)
      canvas->surface[i * canvas->width + j] = with;
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
  return c;
}
