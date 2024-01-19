#ifndef BUFFER_H
#define BUFFER_H

class Buffer {
public:
  Buffer();
  ~Buffer();

  char* getBuffer() const;
  int getLength() const;

  void append(const char *s, int len);

private:
  char *m_buffer;
  int m_length;
};

#endif
