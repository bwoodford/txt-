#include "Terminal.h"
#include "Editor.h"
#include <stdexcept>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {

  try {

    Terminal terminal;
    Cursor cursor(0,0);
    Editor editor(terminal, cursor);

    if (argc >= 2) {
      editor.open(argv[1]);
    }

    while (true) {
      editor.refreshScreen();
      editor.processKeypress();
    }

    // TODO: need to clear the screen on exit
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
  } catch (const runtime_error& ex) {
    // TODO: need to clear the screen on exit
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    cerr << ex.what() << endl;
    return EXIT_FAILURE;
  }

  return 0;
}
