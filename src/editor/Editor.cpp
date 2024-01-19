#include "Editor.h"
#include "AppException.h"
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

char Editor::readKey() {
  int nread;
  char c;

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) throw AppException("Error reading stdin.");
  }

  return c;
}

void Editor::processKeypress() {
  char c = readKey();

  switch (c) {
    case CTRL_KEY('q'):
      exit(0);
      break;
  }
}

void Editor::refreshScreen() {
  // J - erase in display
  write(STDOUT_FILENO, "\x1b[2J", 4);
  // H - set cursor to home position (top left)
  write(STDOUT_FILENO, "\x1b[H", 3);

  drawRows();

  // H - set cursor to home position (top left)
  write(STDOUT_FILENO, "\x1b[H", 3);
}

void Editor::drawRows() {
  int y;
  int rows = m_terminal.getScreenRows();
  for (y = 0; y < rows; y++) {
    write(STDOUT_FILENO, "~", 1);

    if (y < rows - 1) {
      write(STDOUT_FILENO, "\r\n", 2);
    }
  }
}

