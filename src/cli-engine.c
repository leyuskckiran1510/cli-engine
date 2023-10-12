#include <stdio.h>

#include "ansi_codes.h"
#include "canvas.h"
#include "cli-engine.h"
#include "utils/util.h"

void clear_screen() {
#if defined _WIN32 || defined _WIN64
  int __unused = system("cls");
#else
  int __unused = system("clear");
  (void)(__unused);
#endif
}

void reset_all() {
  printf(ANSI_BUFFER1 ANSI_CURSOR(1,1) ANSI_CURSOR_Y ANSI_RESET ANSI_LINE_WRAP_Y);
  reset_terminal_mode();
  clear_screen();
}

Canvas *InitWindow(int width, int height, const char *title) {
  set_conio_terminal_mode();
  Canvas *c = canvas_init(width, height);
  printf(ANSI_CURSOR_N ANSI_BUFFER2);
  clear_screen();
  printf(ANSI_CURSOR_N ANSI_BUFFER1);
  clear_screen();
  printf(ANSI_SET_TITLE_FMT"\n", title);
  atexit(reset_all);
  return c;
}
