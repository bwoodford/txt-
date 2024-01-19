#include "Editor.h"
#include "AppException.h"
#include "Buffer.h"
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

  Buffer buffer;

  // l - set mode (turning cursor off)
  buffer.append("\x1b[?25l", 4);
  // H - set cursor to home position (top left)
  buffer.append("\x1b[H", 3);

  drawRows(&buffer);

  // H - set cursor to home position (top left)
  buffer.append("\x1b[H", 3);
  // h - reset mode (turning cursor on)
  buffer.append("\x1b[?25h", 4);

  write(STDOUT_FILENO, buffer.getBuffer(), buffer.getLength());
}

void Editor::drawRows(Buffer *buffer) {
  int y;
  int rows = m_terminal.getScreenRows();
  for (y = 0; y < rows; y++) {
    buffer->append("~", 1);

    // K - erase in line
    buffer->append("\x1b[K", 3);
    if (y < rows - 1) {
      buffer->append("\r\n", 2);
    }
  }
}

