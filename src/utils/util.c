#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
termios — MAN page
    https://man7.org/linux/man-pages/man3/termios.3.html#DESCRIPTION
    or 
    man 3 termios
*/

#if defined _WIN32 || defined _WIN64
   HANDLE hStdout, hStdin;
   DWORD inMode, inOldMode;//cRead, 
   DWORD outMode, outOldMode;//cRead, 
  void reset_terminal_mode() {
     if(!SetConsoleMode(hStdin, inOldMode)) {
      exit(GetLastError());
    } 
    if(!SetConsoleMode(hStdout, outOldMode)) {
      exit(GetLastError());
    } 
  }//resetting
  void set_conio_terminal_mode() {

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE ||
        hStdout == INVALID_HANDLE_VALUE){
        exit(GetLastError());
    }

    if (! GetConsoleMode(hStdin, &inOldMode)){
       exit(GetLastError());
    }
    if (! GetConsoleMode(hStdout, &outOldMode)){
           exit(GetLastError());
        }

    inMode = inOldMode &
        ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    outMode = outOldMode;
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (! SetConsoleMode(hStdin, inMode)){
       exit(GetLastError());
    }
    if (! SetConsoleMode(hStdout, outMode)){
       exit(GetLastError());
    }
    

}

#else
  struct termios orig_termios;
  void reset_terminal_mode() { tcsetattr(0, TCSANOW, &orig_termios); }//resetting
  void set_conio_terminal_mode() {
    struct termios new_termios;
    tcgetattr(0, &orig_termios); //tc-get-attr , retriving the current terminal console config
    memcpy(&new_termios, &orig_termios, sizeof(new_termios)); //coping the original config
    cfmakeraw(&new_termios); //cf-make-raw , config set to raw mode
    new_termios.c_oflag = orig_termios.c_oflag; // changing the new raw config's output mode to 
                                                // default output as raw output will cause problem 
                                                //while rendering ansi character
    tcsetattr(0, TCSANOW, &new_termios);//tc-set-attr, setting the terminal to new config
  }

#endif



//base64 character set
static char charset[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
                    '3', '4', '5', '6', '7', '8', '9', '+', '/'};


/*
  [Wiki Base64 Encoding] https://en.wikipedia.org/wiki/Base64
*/
char *base64(char *normal) {
  int counter = 0, f_pointer = 0, n_index = 0, c_index = 0, buffer = 0;
  int n_len = strlen(normal);
  char *final = malloc(sizeof(char) * ((n_len * 8 / 6) + 1));

  while (n_index < n_len) {
    c_index = ((buffer << (8 - ((counter % 4) * 2)) |
                normal[n_index] >> ((counter % 4) * 2)) &
               252) >>//0b11111100
              2;
    if (counter % 4 == 0) {
      buffer = normal[n_index] & 3; //0b00000011
    } else if (counter % 4 == 1) {
      buffer = normal[n_index] & 15;//0b00001111
    } else if (counter % 4 == 2) {
      buffer = normal[n_index] & 63;//0b00111111
    } else if (counter % 4 == 3) {
      buffer = 0;
      n_index -= 1;
    }
    final[f_pointer] = charset[c_index];
        counter ++;
        n_index ++;
        f_pointer ++;
  }
  final[f_pointer] = '\0';
  return final;
}

/*
  Copies base64(string) to clipboard
  using OSC (Operating System Command) sequences 52
  https://chromium.googlesource.com/apps/libapps/+/a5fb83c190aa9d74f4a9bca233dac6be2664e9e9/hterm/doc/ControlSequences.md#OSC
*/
void copy_to_clipboard(char *content) {
  char *encoded = base64(content);
  printf("\033]52;c;%s\a", encoded);
  free(encoded);
}


/*
[UTF-8 encoding table](https://en.wikipedia.org/wiki/UTF-8#Encoding)
<hr>
  U+0000  U+007F    0xxxxxxx <br>
  U+0080  U+07FF    110xxxxx  10xxxxxx <br>
  U+0800  U+FFFF    1110xxxx  10xxxxxx  10xxxxxx <br>
  U+10000 U+10FFFF  11110xxx  10xxxxxx  10xxxxxx  10xxxxxx
<hr>
[UTF-8 wiki](https://en.wikipedia.org/wiki/UTF-8#Encoding_process) for basic
explanation [UTF-8,format of ISO
10646](https://datatracker.ietf.org/doc/html/rfc3629#section-3)for more detail
*/
void unsigned_to_unicode(unsigned int x, char *buffer) {
  /*
    offset_x + mask_x = 255
  */
  unsigned int offset_0 = 128; // 0b10000000
  unsigned int offset_1 = 192; // 0b11000000
  unsigned int offset_2 = 224; // 0b11100000
  unsigned int offset_3 = 240; // 0b11110000

  unsigned int mask_0 = 127; // 0b01111111
  unsigned int mask_1 = 63;  // 0b00111111
  unsigned int mask_2 = 31;  // 0b00011111
  unsigned int mask_3 = 7;   // 0b00000111

  if (x <= 0x007F) {
    buffer[0] = (x >> 8 * 0) & mask_0;
  } else if (x >= 0x0080 && x <= 0x07FF) {
    buffer[1] = offset_0 | ((x >> 8 * 0) & mask_1);
    buffer[0] = offset_1 | ((x >> 6 * 1) & mask_2);
  } else if (x >= 0x0800 && x <= 0xFFFF) {
    buffer[2] = offset_0 | ((x >> 8 * 0) & mask_1);
    buffer[1] = offset_0 | ((x >> 6 * 1) & mask_1);
    buffer[0] = offset_2 | ((x >> 6 * 2) & mask_2);
  } else if (x >= 0x10000 && x <= 0x10FFFF) {
    buffer[3] = offset_0 | ((x >> 8 * 0) & mask_1);
    buffer[2] = offset_0 | ((x >> 6 * 1) & mask_1);
    buffer[1] = offset_0 | ((x >> 6 * 2) & mask_2);
    buffer[0] = offset_3 | ((x >> 6 * 3) & mask_3);
  }
  else{
    strcpy(buffer,"\0");
  }
}

vec2i get_terminal_size(){
  struct winsize w;
  vec2i temp;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  temp.x = w.ws_col;
  temp.y = w.ws_row;
  return temp;
}

