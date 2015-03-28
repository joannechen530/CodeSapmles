#ifndef _ARRAYQUEUE_CPP
#define _ARRAYQUEUE_CPP

//ArrayQueue.cpp

#include "ArrayQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
using namespace std;

ArrayQueue::ArrayQueue()   
{
  // Constructor: initialize member variables
  //              and do any other initialization
  //              needed (if any)
  array = new PuzzleState*[INIT_SIZE];
  capacity = INIT_SIZE;
  front = back = size = 0;
}

void ArrayQueue::add(PuzzleState *elem)
{
  ensure_capacity(size+1); 
  array[back] = elem;
  back = (back + 1) % capacity;
  size++;
}

PuzzleState* ArrayQueue::remove()
{
  assert(!is_empty());
  PuzzleState* temp = array[front];
  front = (front + 1) % capacity;
  size--;
  return temp;
}

bool ArrayQueue::is_empty()
{
  return (front == back);
}

void ArrayQueue::ensure_capacity(int n){
  if (capacity <= n) {
    int target_capacity = (2*capacity > n) ? 2*capacity : n;
    PuzzleState** oldarray = array;
    array = new PuzzleState*[target_capacity];

    for (int i=front; i<front + size; i++)
      array[i % target_capacity] = oldarray[i % capacity];

    back = (front+size) % target_capacity;
    capacity = target_capacity;

    delete [] oldarray;
  }
}



ArrayQueue::~ArrayQueue(){
  delete [] array;
}

#endif
