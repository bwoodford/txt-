#include "Node.h"


Node::Node(int start, int length):
  m_start(start), m_length(length) {
  m_type = Type::Original;
}
