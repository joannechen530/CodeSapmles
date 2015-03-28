//HeapPriorityQueue.hpp
#ifndef _HEAPPRIORITYQUEUE_HPP
#define _HEAPPRIORITYQUEUE_HPP


#include <vector>

#include "BagOfPuzzleStates.hpp"

class HeapPriorityQueue : public BagOfPuzzleStates
  {
  public:
    HeapPriorityQueue();
    PuzzleState *remove();
    void add(PuzzleState *element);
    PuzzleState *get_next();
    bool is_empty();
    ~HeapPriorityQueue();
    void swap_up(int n);
    void swap_down(int n);
    void heapify();

    
  private:
    vector<PuzzleState*> heap;
  };

#endif
