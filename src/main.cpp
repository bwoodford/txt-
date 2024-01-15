#include "Terminal.h"
#include "TerminalException.h"
#include "AppException.h"
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>

using namespace std;

int main() {

  try {

    Terminal terminal;

    while (true) {
      char c = '\0';
      if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
        throw new AppException("Error reading input");
      cout << "Read: " << c << endl;

      if (c == 'q') break;
    }

  } catch (const TerminalException& e) {
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }

  return 0;
}
