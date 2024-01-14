#include "terminal/terminal.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main() {
  
  Terminal();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    cout << "Read: " << c << endl;
  }

  return 0;
}
