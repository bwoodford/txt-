#ifndef ROW_H
#define ROW_H

class Row {
public:
  Row(char* chars, int size): 
    m_chars(chars), m_size(size) {

  }

  int getSize() const;
  char* getChars() const;

private:
  int m_size;
  char* m_chars;
};

#endif
