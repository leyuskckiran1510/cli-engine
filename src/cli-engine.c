#include "cli-engine.h"
#include "canvas.h"
#include "utils/util.h"
#include <stdio.h>

#define ST "\0"

void clear_screen(){
#ifdef __DOS__
  system("cls");
#else
  if(system("clear")){
    
  };
#endif
}

void reset_all(){
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