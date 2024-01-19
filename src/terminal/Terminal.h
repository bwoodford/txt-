#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

class Terminal {
public:
  Terminal();

  int getScreenRows() const;
  int getScreenCols() const;

private:
  int screenRows;
  int screenCols;

  static void enableRawMode();
  static struct termios orig_termios;
  static void disableRawMode();

  void setWindowSize();
  void getCursorPosition();
};

#endif
