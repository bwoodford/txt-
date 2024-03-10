#include "Row.h"
#include <string.h>

int Row::getSize() const {
  return m_size;
}

char* Row::getChars() const {
  return m_chars;
}

void Row::insert(int at, char c) {
  memmove(&m_chars[at + 1], &m_chars[at], m_size - at + 1);
  m_size += 1;
  m_chars[at] = c;
}
