#include "Editor.h"
#include "AppException.h"
#include "Sequences.h"
#include "Buffer.h"
#include "TextManager.h"
#include <cstdio>
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

Editor::Editor(const Terminal& terminal, Cursor& cursor, TextManager& textManager): 
    m_terminal(terminal), m_cursor(cursor), m_text(textManager) {
  m_rowoff = 0;
  m_coloff = 0;
}

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

    default:
      insert(c);
      break;
  }
}

void Editor::insert(char c) {
  if (m_cursor.getY() == m_text.getNumRows()) {
    m_text.appendRow((char*)"", 0);
  }
  m_text.insertIntoRow(m_text.getRows()[m_cursor.getY()], m_cursor.getX(), c);
  m_cursor.setX(m_cursor.getX() + 1);
}

void Editor::moveCursor(char key) {
  Row *row = (m_cursor.getY() >= m_text.getNumRows()) ? nullptr : &m_text.getRows()[m_cursor.getY()];

  switch (key) {
    case 'h':
      if (m_cursor.getX() != 0) {
        m_cursor.left();
      }
      break;
    case 'l':
      m_cursor.right();
      break;
    case 'k':
      if (m_cursor.getY() != 0) {
        m_cursor.up();
      }
      break;
    case 'j':
      if (m_cursor.getY() < m_text.getNumRows()) {
        m_cursor.down();
      }
      break;
  }
  
  // Snap cursor to the end of the line
  row = (m_cursor.getY() >= m_text.getNumRows()) ? nullptr : &m_text.getRows()[m_cursor.getY()];
  int rowlen = row ? row->getSize(): 0;
  if (m_cursor.getX() > rowlen) {
    m_cursor.setX(rowlen);
  }

}

void Editor::scroll() {
  // Above visible window
  if (m_cursor.getY() < m_rowoff) {
    m_rowoff = m_cursor.getY();
  }
  // Below visible window
  if (m_cursor.getY() >= m_rowoff + m_terminal.getScreenRows()) {
    m_rowoff = m_cursor.getY() - m_terminal.getScreenRows() + 1;
  }
  // Left of visible window
  if (m_cursor.getX() < m_coloff) {
    m_coloff = m_cursor.getX();
  }
  // Right of visible window
  if (m_cursor.getX() >= m_coloff + m_terminal.getScreenCols()) {
    m_coloff = m_cursor.getX() - m_terminal.getScreenCols() + 1;
  }
}

void Editor::refreshScreen() {
  scroll();

  Buffer buffer;

  buffer.append(CURSOR_OFF, CURSOR_OFF_LENGTH);
  buffer.append(SET_CURSOR_HOME, SET_CURSOR_HOME_LENGTH);

  drawRows(&buffer);

  char buf[32];
  // Add one to cords to make cursor 1-indexed like the terminal
  snprintf(buf, sizeof(buf), SET_CURSOR_Y_X, 
           (m_cursor.getY() - m_rowoff) + 1, (m_cursor.getX() - m_coloff) + 1);
  buffer.append(buf, strlen(buf));

  buffer.append(CURSOR_ON, CURSOR_ON_LENGTH);

  write(STDOUT_FILENO, buffer.getBuffer(), buffer.getLength());
}

void Editor::drawRows(Buffer *buffer) {
  int y;
  int rows = m_terminal.getScreenRows();
  for (y = 0; y < rows; y++) {
    int filerow = y + m_rowoff;
    if(filerow >= m_text.getNumRows()) {
      buffer->append("~", 1);
    } else {
      int length = m_text.getRows()[filerow].getSize() - m_coloff;

      if (length < 0) length = 0;
      if (length > m_terminal.getScreenCols()) length = m_terminal.getScreenCols();

      char* chars = m_text.getRows()[filerow].getChars();
      buffer->append(&chars[m_coloff], length);
    }

    buffer->append(CLEAR_LINE, CLEAR_LINE_LENGTH);
    if (y < rows - 1) {
      buffer->append("\r\n", 2);
    }
  }
}

void Editor::open(char* filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) throw AppException("Error opening file.");

  char *line = nullptr;
  size_t linecap = 0;
  ssize_t linelen;

  while ((linelen = getline(&line, &linecap, fp)) != -1) {
    while(linelen > 0 && (line[linelen-1] == '\n' || line[linelen-1] == '\r'))
      linelen--;
    m_text.appendRow(line, linelen);
  }

  free(line);
  fclose(fp);
}
