
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
}