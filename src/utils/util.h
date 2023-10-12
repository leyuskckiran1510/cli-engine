#ifndef __CE_UTIL__
#define __CE_UTIL__

#ifdef __APPLE__
	#include <unistd.h>
	#include <termios.h>
	#include <fcntl.h>
#elif defined _WIN32 || defined _WIN64
	#include <wchar.h>
	#include <windows.h>
	#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
		#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
	#endif
#else
	#include <unistd.h>
	#include <termios.h>
  #include <sys/ioctl.h>
#endif

typedef struct {
  int x,y;
}vec2i;

typedef struct {
  float x,y;
}vec2f;




void unsigned_to_unicode(unsigned int x,char *buffer);
void reset_terminal_mode();
void set_conio_terminal_mode();
void copy_to_clipboard(char*);
char *base64(char *);
vec2i get_terminal_size();




#endif