#ifndef NODE_H
#define NODE_H

class Node {
public:
  enum Type {
    Original,
    Added,
    Deleted
  }; 

  Node(int start, int length);

private:
  Type m_type;
  int m_start;
  int m_length;
};

#endif
