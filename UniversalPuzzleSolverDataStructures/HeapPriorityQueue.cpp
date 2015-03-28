//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
	// nothing to initialize
}

HeapPriorityQueue::~HeapPriorityQueue() {
  // nothing to be deallocated
}

void HeapPriorityQueue::add(PuzzleState *elem) {
	heap.push_back(elem);
	swap_up(heap.size()-1);

}

PuzzleState * HeapPriorityQueue::remove() {
	assert(!is_empty());
	PuzzleState* ret = heap[0];
	heap[0] = heap.back();
	heap.erase(heap.begin() + heap.size()-1);
	heapify();
	return ret;

}

void HeapPriorityQueue::swap_up(int n){
	if (n < 1) return;
	int parent = (n-1)/2;
	if (heap[n]->getBadness() < heap[parent]->getBadness()) {
		PuzzleState* temp = heap[parent];
		heap[parent] = heap[n];
		heap[n] = temp;
		swap_up(parent);
	}
}

void HeapPriorityQueue::swap_down(int n){
	int left = 2*n + 1;
	int right = 2*n + 2;
	int min = n;
	if (right < heap.size() && heap[right]->getBadness() < heap[n]->getBadness()) 
		min = right;
	if (left < heap.size() && heap[left] < heap[right] && heap[left]->getBadness() < heap[n]->getBadness())
		min = left;
	if (min != n) {
		PuzzleState* temp = heap[min];
		heap[min] = heap[n];
		heap[n] = temp;
		swap_down(min);
	}
}

void HeapPriorityQueue::heapify(){
	int last_parent = (heap.size()-2)/2;
	for (int i = last_parent; i>=0; i--)
		swap_down(i);

}

PuzzleState *HeapPriorityQueue::get_next() {
	return heap.front();

}

bool HeapPriorityQueue::is_empty() {
	return (heap.size()==0);
}

#endif
