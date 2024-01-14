#include "terminal.h"
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>

Terminal::Terminal() {
  enableRawMode();
}

void Terminal::disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void Terminal::enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
