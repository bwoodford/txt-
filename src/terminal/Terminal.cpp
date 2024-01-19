#include "Terminal.h"
#include "TerminalException.h"
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

struct termios Terminal::orig_termios;

Terminal::Terminal() {
  enableRawMode();
  setWindowSize();
}

int Terminal::getScreenCols() const {
  return screenCols;
}

int Terminal::getScreenRows() const {
  return screenRows;
}

void Terminal::setWindowSize() {
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    // Move the cursor right and down
    // C - Cursor forward
    // B - Cursor down
    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
      throw TerminalException("Unable to set terminal window size.");
    getCursorPosition();
  } else {
    screenCols = ws.ws_col;
    screenRows = ws.ws_row;
  }
}

void Terminal::getCursorPosition() {
  char buf[32];
  unsigned int i = 0;

  // Get current cursor position
  // n - Device status report
  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) 
    throw TerminalException("Error writing cursor to terminal.");

  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0';

  if (buf[0] != '\x1b' || buf[1] != '[')
    throw TerminalException("Error parsing cursor position.");
  if (sscanf(&buf[2], "%d;%d", &screenRows, &screenCols) != 2)
    throw TerminalException("Error setting screen rows and columns.");
}

void Terminal::disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void Terminal::enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    throw TerminalException("Error getting terminal attributes.");

  atexit(disableRawMode);
  struct termios raw = orig_termios;

  // IXON - transmission start and stop
  // ICRNL - carriage return to new line
  // BRKINT - break condition
  // INPCK - parity checking
  // ISTRIP - strip 8th bit on each input byte
  raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
  // OPOST - output processing
  raw.c_oflag &= ~(OPOST);
  // CS8 - set character size to 8 bits per byte
  raw.c_cflag |= (CS8);
  // ECHO - typed output is shown on the terminal
  // ICANON - canonical mode
  // ISIG - input signaling
  // IEXTEN - weird modifier CTRL-V key thing
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  // Minimum number of input bytes needed before read() returns
  raw.c_cc[VMIN] = 0;
  // Maximum amount of time to wait before read() returns 
  // - in tenths of seconds
  raw.c_cc[VTIME] = 1;

  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    throw TerminalException("Error setting terminal attributes.");
}
