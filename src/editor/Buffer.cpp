#include "Buffer.h"
#include <cstdlib>
#include <cstring>

Buffer::Buffer() {
  m_buffer = nullptr;
  m_length = 0;
}

Buffer::~Buffer() {
  free(m_buffer);
}

char* Buffer::getBuffer() const {
  return m_buffer;
}

int Buffer::getLength() const {
  return m_length;
}

void Buffer::append(const char *string, int length) {
  char *newBuff = (char *)realloc(m_buffer, m_length + length);

  if(newBuff == nullptr) return;
  memcpy(&newBuff[m_length], string, length);

  m_buffer = newBuff;
  m_length += length;
}
