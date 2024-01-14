#include "Terminal.h"
#include "TerminalException.h"
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main() {

  try {

    Terminal terminal;

    while (true) {
      char c = '\0';
      read(STDIN_FILENO, &c, 1);
      cout << "Read: " << c << endl;

      if (c == 'q') break;
    }

  } catch (const TerminalException& e) {
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }

  return 0;
}
