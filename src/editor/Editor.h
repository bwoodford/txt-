#ifndef EDITOR_H
#define EDITOR_H

#include "Terminal.h"
#include "TextManager.h"
#include "Cursor.h"
#include "Buffer.h"

class Editor {
public:
  Editor(const Terminal& terminal, Cursor& cursor, TextManager& textManager);

  void processKeypress();
  void refreshScreen();
  void open(char* filename);

private:
  const Terminal& m_terminal;
  Cursor& m_cursor;
  TextManager& m_text;

  int m_rowoff;
  int m_coloff;

  char readKey();
  void drawRows(Buffer *buffer);
  void moveCursor(char key);
  void scroll();

  void insert(char c);
};

#endif
