
/*
[UTF-8 encoding table](https://en.wikipedia.org/wiki/UTF-8#Encoding)
<hr>
  U+0000  U+007F    0xxxxxxx <br>
  U+0080  U+07FF    110xxxxx  10xxxxxx <br>
  U+0800  U+FFFF    1110xxxx  10xxxxxx  10xxxxxx <br>
  U+10000 U+10FFFF  11110xxx  10xxxxxx  10xxxxxx  10xxxxxx
<hr>
[UTF-8 wiki](https://en.wikipedia.org/wiki/UTF-8#Encoding_process) for basic explanation
[UTF-8,format of ISO 10646](https://datatracker.ietf.org/doc/html/rfc3629#section-3)for more detail
*/
void unsigned_to_unicode(unsigned int x,char *buffer){
  if (x <= 0x007f) {
    buffer[0] = (x >> 8 * 0) & 0b1111111;
  } else if (x >= 0x0080 && x <= 0x07FF) {
    buffer[1] = 0b10000000 | ((x >> 8 * 0) & 0b0111111);
    buffer[0] = 0b11000000 | ((x >> 6 * 1) & 0b0011111);
  } else if (x >= 0x0800 && x <= 0xFFFF) {
    buffer[2] = 0b10000000 | ((x >> 8 * 0) & 0b00111111);
    buffer[1] = 0b10000000 | ((x >> 6 * 1) & 0b00111111);
    buffer[0] = 0b11100000 | ((x >> 6 * 2) & 0b00011111);
  } else if (x >= 0x10000 && x <= 0x10FFFF) {
    buffer[3] = 0b10000000 | ((x >> 8 * 0) & 0b0111111);
    buffer[2] = 0b10000000 | ((x >> 6 * 1) & 0b00111111);
    buffer[1] = 0b10000000 | ((x >> 6 * 2) & 0b00011111);
    buffer[0] = 0b11110000 | ((x >> 6 * 3) & 0b0000111);
  }
}