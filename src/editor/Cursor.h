#ifndef CURSOR_H
#define CURSOR_H

class Cursor {
public:
  Cursor(int x, int y): m_x(x), m_y(y) {
  }

  void left();
  void right();
  void up();
  void down();

  int getX() const;
  int getY() const;

private:
  int m_x;
  int m_y;
};

#endif
