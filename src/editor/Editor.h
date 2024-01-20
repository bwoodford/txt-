#ifndef EDITOR_H
#define EDITOR_H

#include "Terminal.h"
#include "Cursor.h"
#include "Buffer.h"

class Editor {
public:
  Editor(const Terminal& terminal, const Cursor& cursor): 
    m_terminal(terminal), m_cursor(cursor){

  }
  void processKeypress();
  void refreshScreen();
private:
  const Terminal& m_terminal;
  const Cursor& m_cursor;
  char readKey();
  void drawRows(Buffer *buffer);
};

#endif
