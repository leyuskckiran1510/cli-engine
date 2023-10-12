#include "cli-engine.h"
#include "canvas.h"
#include "utils/util.h"
#include <stdio.h>

void clear_screen(){
#if defined _WIN32 || defined _WIN64
  int __unused = system("cls");
#else
  int __unused = system("clear");
  (void)(__unused);
#endif
}

void reset_all(){
  printf("\x1b[?1049h\033[1;1H\033[?25h\x1b[?7h\x1b[0m\x1b[m");
  reset_terminal_mode();
  clear_screen();
}

Canvas* InitWindow(int width, int height, const char *title){
  set_conio_terminal_mode();
  Canvas *c = canvas_init(width,height);
  printf("\x1b[?25l\x1b[?7l");
  printf("\x1b]0;%s\a\n",title);
  atexit(reset_all);
  return c;
}
