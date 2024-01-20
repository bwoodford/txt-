#ifndef CURSOR_H
#define CURSOR_H

class Cursor {
public:
  Cursor(int x, int y): m_x(x), m_y(y) {
  }

  int getX() const;
  void setX(int x);

  int getY() const;
  void setY(int y);

private:
  int m_x;
  int m_y;
};

#endif
