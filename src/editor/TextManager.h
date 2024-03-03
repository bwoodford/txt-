#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include "Row.h"

class TextManager {
public:
  TextManager();
  ~TextManager();

  void load();
  void appendRow(char *string, long length);

  int getNumRows() const;
  Row* getRows() const;

private:
  Row *m_rows;
  int m_numrows;

  Row updateRow(Row& row);
};

#endif
