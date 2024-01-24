#ifndef EDITOR_H
#define EDITOR_H

#include "Row.h"
#include "Terminal.h"
#include "Cursor.h"
#include "Buffer.h"

class Editor {
public:
  Editor(const Terminal& terminal, Cursor& cursor);
  ~Editor();

  void processKeypress();
  void refreshScreen();
  void open(char* filename);

private:
  const Terminal& m_terminal;
  Cursor& m_cursor;
  Row *m_rows;  

  int m_numrows;
  int m_rowoff;
  int m_coloff;

  char readKey();
  void drawRows(Buffer *buffer);
  void moveCursor(char key);
  void appendRow(char *string, long length);
  void scroll();
};

#endif
