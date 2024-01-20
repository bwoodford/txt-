#include "Editor.h"
#include "AppException.h"
#include "Sequences.h"
#include "Buffer.h"
#include <cstring>
#include <unistd.h>

using Sequences::CURSOR_OFF;
using Sequences::CURSOR_OFF_LENGTH;

using Sequences::CURSOR_ON;
using Sequences::CURSOR_ON_LENGTH;

using Sequences::SET_CURSOR_HOME;
using Sequences::SET_CURSOR_HOME_LENGTH;

using Sequences::SET_CURSOR_Y_X;

using Sequences::CLEAR_LINE;
using Sequences::CLEAR_LINE_LENGTH;

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

    case 'h':
    case 'l':
    case 'j':
    case 'k':
      moveCursor(c);
      break; 
  }
}

void Editor::moveCursor(char key) {
  switch (key) {
    case 'h':
      if (m_cursor.getX() != 0) {
        m_cursor.left();
      }
      break;
    case 'l':
      if (m_cursor.getX() != m_terminal.getScreenCols() - 1) {
        m_cursor.right();
      }
      break;
    case 'k':
      if (m_cursor.getY() != 0) {
        m_cursor.up();
      }
      break;
    case 'j':
      if (m_cursor.getY() != m_terminal.getScreenRows() - 1) {
        m_cursor.down();
      }
      break;
  }
}

void Editor::refreshScreen() {

  Buffer buffer;

  buffer.append(CURSOR_OFF, CURSOR_OFF_LENGTH);
  buffer.append(SET_CURSOR_HOME, SET_CURSOR_HOME_LENGTH);

  drawRows(&buffer);

  char buf[32];
  // Add one to cords to make cursor 1-indexed like the terminal
  snprintf(buf, sizeof(buf), SET_CURSOR_Y_X, m_cursor.getY() + 1, m_cursor.getX() + 1);
  buffer.append(buf, strlen(buf));

  buffer.append(CURSOR_ON, CURSOR_ON_LENGTH);

  write(STDOUT_FILENO, buffer.getBuffer(), buffer.getLength());
}

void Editor::drawRows(Buffer *buffer) {
  int y;
  int rows = m_terminal.getScreenRows();
  for (y = 0; y < rows; y++) {
    buffer->append("~", 1);

    buffer->append(CLEAR_LINE, CLEAR_LINE_LENGTH);
    if (y < rows - 1) {
      buffer->append("\r\n", 2);
    }
  }
}

