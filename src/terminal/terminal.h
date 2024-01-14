#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

class Terminal {
public:
  Terminal();
private:
  static void enableRawMode();
  static struct termios orig_termios;
  static void disableRawMode();
};

#endif
