#ifndef __CE_UTIL__
#define __CE_UTIL__

#include <stdlib.h>
#include <string.h>
#include <termios.h>


#ifndef __UNICODE__
#define __UNICODE__ 8
void unsigned_to_unicode(unsigned int x,char *buffer);
#endif

void reset_terminal_mode();
void set_conio_terminal_mode();
void copy_to_clipboard(char*);
char *base64(char *);

#endif