#include "Terminal.h"
#include "TerminalException.h"
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>

struct termios Terminal::orig_termios;

Terminal::Terminal() {
  enableRawMode();
}

void Terminal::disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void Terminal::enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    throw new TerminalException("Error in tcgetattr");

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
    throw new TerminalException("Error in tcsetattr");
}
