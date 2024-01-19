#ifndef EDITOR_H
#define EDITOR_H

#include "Terminal.h"

class Editor {
public:
  Editor(const Terminal& terminal): m_terminal(terminal) {

  }
  void processKeypress();
  void refreshScreen();
private:
  const Terminal& m_terminal;
  char readKey();
  void drawRows();
};

#endif
