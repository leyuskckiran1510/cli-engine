#include "cli-engine.h"
#include "canvas.h"
#include "utils/util.h"
#include <stdio.h>

#define ST "\0"

void clear_screen(){
#ifdef __APPLE__
#elif defined _WIN32 || defined _WIN64
  system("cls");
#else
  system("clear");
#endif
}

void reset_all(){
  printf("\x1b[0m");
  reset_terminal_mode();
  clear_screen();
}

Canvas* InitWindow(int width, int height, const char *title){
  set_conio_terminal_mode();
  Canvas *c = canvas_init(width,height);
  printf("\033]0;%s\a\033]m",title);
  atexit(reset_all);
  return c;
}