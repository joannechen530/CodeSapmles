//LinkedListQueue.cpp
#ifndef _LINKEDLISTQUEUE_CPP
#define _LINKEDLISTQUEUE_CPP

#include "LinkedListQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
LinkedListQueue::LinkedListQueue()  
{
	head = tail = NULL;
	size = 0;
}

void LinkedListQueue::add(PuzzleState *elem)
{
	if (is_empty())
		head = tail = new node;
	else {
		node* temp = new node;
		tail->next = temp;
		tail = temp;
	}
	size++;
	tail->data = elem;
	tail->next = NULL;
}

PuzzleState *LinkedListQueue::remove()
{
	assert(!is_empty());
	PuzzleState* result = head->data;
	node* temp = head->next;
	size--;
	delete head;
	head = temp;
	if (is_empty()) tail = NULL;

	return result;
}

bool LinkedListQueue::is_empty()
{
	return (head == NULL);
}

LinkedListQueue::~LinkedListQueue()
{
	while (head) {
		remove();
	}

}

#endif

