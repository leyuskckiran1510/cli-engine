#include <poll.h>
#include <unistd.h>

char keypress() {
  int poll_count = 1;
  int timeout = 0;
  struct pollfd input[] = {{.events = POLLIN}};
  if (poll(input, poll_count, timeout)) {
    unsigned char buffer;
    if (read(0, &buffer, sizeof(buffer))>0) {
      return buffer;
    }
  }
  return 0;
}
