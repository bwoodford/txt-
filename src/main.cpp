#include "Terminal.h"
#include "Editor.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int main() {

  try {

    Terminal terminal;
    Editor editor;

    while (true) {
      editor.processKeypress();
    }

  } catch (const runtime_error& ex) {
    cerr << ex.what() << endl;
    return EXIT_FAILURE;
  }

  return 0;
}
