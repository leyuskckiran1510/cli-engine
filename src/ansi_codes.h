#ifndef __ANSI_CODES__
#define __ANSI_CODES__

#define ESC "\x1b"

// CONFIG CODES
#define ANSI_RESET         ESC "[0m"
#define ANSI_SET_TITLE_FMT ESC "]0;%s\a"

//Clear Screen
#define ANSI_CLR           ESC "[0J" ESC "[1J" ESC "[2J" //ESC "[3J"
#define ANSI_CLR_TOP       ESC "[0J"
#define ANSI_CLR_BOTTOM    ESC "[1J"
#define ANSI_CLR_SCREEN    ESC "[2J"
#define ANSI_CLR_BUFFER    ESC "[3J"

//DISPLAY BUFFER CODES
#define ANSI_BUFFER1       ESC "[?1049h"
#define ANSI_BUFFER2       ESC "[?1049l"

//LINE FEED CODES 
#define ANSI_LINE_WRAP_Y   ESC "[?7h"
#define ANSI_LINE_WRAP_N   ESC "[?7h"

//CURSORS CODES
#define ANSI_CURSOR_Y      ESC "[?25h"
#define ANSI_CURSOR_N      ESC "[?25l"
#define ANSI_CURSOR_PING   ESC "[6n"
#define ANSI_CURSOR(x, y)  ESC "[" #x ";" #y "H"

//COLOR CODES
#define ANSI_FG_RGB_FMT    ESC "[38;2;%03d;%03d;%03dm"
#define ANSI_BG_RGB_FMT    ESC "[48;2;%03d;%03d;%03dm"
#define ANSI_FGBG_RGB_FMT  ESC "[38;2;%03d;%03d;%03d;48;2;%03d;%03d;%03dm"


#endif