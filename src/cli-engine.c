#include <stdio.h>

#include "ansi_codes.h"
#include "canvas.h"
#include "cli-engine.h"
#include "utils/util.h"


void clear_screen(){
  // resetting/clearing both output buffers
  printf(ANSI_BUFFER1);
  printf(ANSI_CLR);
  printf(ANSI_BUFFER2);
  printf(ANSI_CLR);
}

void reset_all() {
  reset_terminal_mode();
  clear_screen();
  printf(ANSI_BUFFER1 ANSI_CURSOR(1,1) ANSI_CURSOR_Y ANSI_RESET ANSI_LINE_WRAP_Y);
}

Canvas *InitWindow(int width, int height, const char *title) {
  set_conio_terminal_mode();
  Canvas *c = canvas_init(width, height);
  clear_screen();
  printf(ANSI_SET_TITLE_FMT"\n", title);
  atexit(reset_all);
  return c;
}
