#ifndef EDITOR_H
#define EDITOR_H

class Editor {
public:
  void processKeypress();
private:
  char readKey();
};

#endif
