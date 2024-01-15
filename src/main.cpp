#include "Terminal.h"
#include "AppException.h"
#include <cstdlib>
#include <stdexcept>
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
      // cygwin set errno to EAGAIN on error
      if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
        throw AppException("Error reading input");
      cout << "Read: " << c << endl;

      if (c == 'q') break;
    }

  } catch (const runtime_error& ex) {
    cerr << ex.what() << endl;
    return EXIT_FAILURE;
  }

  return 0;
}
