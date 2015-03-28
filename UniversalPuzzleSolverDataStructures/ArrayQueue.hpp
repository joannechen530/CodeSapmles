//ArrayQueue.hpp
#ifndef _ARRAYQUEUE_HPP
#define _ARRAYQUEUE_HPP

#include "BagOfPuzzleStates.hpp"

class ArrayQueue: public BagOfPuzzleStates
{
 public:
  ArrayQueue(); // constructor
  
  // TodoList interface
  void add(PuzzleState *elem);
  PuzzleState *remove();
  bool is_empty();

  ~ArrayQueue(); // destructor

static const int INIT_SIZE = 5;

 private:
  void ensure_capacity(int n);

  PuzzleState **array;

  int front;
  int back;
  int capacity;
  int size;
};

#endif
