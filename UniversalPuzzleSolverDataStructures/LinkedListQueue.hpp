//LinkedListQueue.hpp
#ifndef _LINKEDLISTQUEUE_HPP
#define _LINKEDLISTQUEUE_HPP

#include "PuzzleState.hpp"
#include "BagOfPuzzleStates.hpp"


class LinkedListQueue: public BagOfPuzzleStates
{
 public:
  LinkedListQueue();
  void add(PuzzleState *elem);
  PuzzleState *remove();
  bool is_empty();
  virtual ~LinkedListQueue();

 private:
  struct node{
    node* next;
    PuzzleState *data;
  };
    
  node* head;
  node* tail;
  int size;
};

#endif
