#include "Cursor.h"


void Cursor::up() {
  m_y--;
}

void Cursor::setX(int x) {
  m_x = x;
}

void Cursor::down() {
  m_y++;
}

void Cursor::left() {
  m_x--;
}

void Cursor::right() {
  m_x++;
}

int Cursor::getX() const {
  return m_x;
}

int Cursor::getY() const {
  return m_y;
}

