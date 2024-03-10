#include "TextManager.h"
#include <cstdlib>
#include <cstring>

#define TAB_LENGTH 8

TextManager::TextManager() {
  m_numrows = 0;
  m_rows = nullptr;
}

TextManager::~TextManager() {
  free(m_rows);
}

int TextManager::getNumRows() const {
   return m_numrows;
}

Row* TextManager::getRows() const {
   return m_rows;
}

void TextManager::appendRow(char* string, long length) {
  m_rows = (Row*)realloc(m_rows, sizeof(Row) * (m_numrows + 1));

  char* buf = (char*)malloc(length+1);
  memcpy(buf, string, length);
  buf[length] = '\0';

  Row tmp = Row(buf, length);
  // Do yo conversions in here
  m_rows[m_numrows] = updateRow(tmp);

  m_numrows++;
}

Row TextManager::updateRow(Row& row) {
  int tabs = 0;
  char* read = row.getChars();

  for(int i=0; i < row.getSize(); i++)
    if (read[i] == '\t') tabs++;

  int length = row.getSize() + (TAB_LENGTH-1) * tabs;
  char* buf = (char*)malloc(length);

  int i,j = 0;
  for(i=0; i < row.getSize(); i++) {
    if (read[i] == '\t') {
      buf[j++] = ' ';
      while(j % TAB_LENGTH != 0) buf[j++] = ' ';
    } else {
      buf[j++] = read[i];
    }
  }
  return Row(buf, length);
}

void TextManager::insertIntoRow(Row& row, int at, int c) {
  if (at < 0 || at > row.getSize()) at = row.getSize();
  row.insert(at, c);
  updateRow(row);
}
