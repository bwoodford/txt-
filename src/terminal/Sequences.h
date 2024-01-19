#ifndef SEQUENCES_H
#define SEQUENCES_H

namespace Sequences {

  static const char* ESCAPE = "\x1b";
  static const char* OPEN_BRACKET = "[";

  // n - Device status report (6 is cursor)
  static const char* CURSOR_POSITION = "\x1b[6n";
  static const int CURSOR_POSITION_LENGTH = 4;

  // C - Cursor forward
  // B - Cursor down
  static const char* MAX_CURSOR_POSITION = "\x1b[999C\x1b[999B";
  static const int MAX_CURSOR_POSITION_LENGTH = 12;
  
  // l - set mode (turning cursor off)
  static const char* CURSOR_OFF = "\x1b[?25l";
  static const int CURSOR_OFF_LENGTH = 4;

  // h - reset mode (turning cursor on)
  static const char* CURSOR_ON = "\x1b[?25h";
  static const int CURSOR_ON_LENGTH = 4;

  static const char* SET_CURSOR_HOME = "\x1b[H";
  static const int SET_CURSOR_HOME_LENGTH = 3;

  // K - erase in line (default erases from cursor to end)
  static const char* CLEAR_LINE = "\x1b[K";
  static const int CLEAR_LINE_LENGTH = 3;
  
}

#endif
