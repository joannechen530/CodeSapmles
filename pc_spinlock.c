#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "uthread.h"
#include "spinlock.h"

#define MAX_ITEMS 10

/* 
 * Classic Consumer and Producer Problem 
 * with an equal number of producers and consumers
 */

int items = 0;
spinlock_t lock;

const int NUM_ITERATIONS = 200;
int NUM_CONSUMERS  = 2;
int NUM_PRODUCERS  = 2;

int producer_wait_count;     // # of times producer had to wait
int consumer_wait_count;     // # of times consumer had to wait
int histogram [MAX_ITEMS+1]; // histogram [i] == # of times list stored i items

void produce() {
  while(1) {
    while (items >= MAX_ITEMS) {
      spinlock_lock(&lock);
      producer_wait_count++;
      spinlock_unlock(&lock);
    }
    spinlock_lock(&lock);
    if (items < MAX_ITEMS) {
      break;
    } else {
      spinlock_unlock(&lock);
    }
  }
  items++;
  histogram [items] += 1;
  assert (items <= MAX_ITEMS);
  spinlock_unlock(&lock);
}

void consume() {
  while(1) {
    while (items <= 0) {
      spinlock_lock(&lock);
      consumer_wait_count++;
      spinlock_unlock(&lock);
    }
    spinlock_lock(&lock);
    if (items > 0) {
      break;
    } else {
      spinlock_unlock(&lock);
    }
  }
  items--;
  histogram [items] += 1;
  assert (items >= 0);
  spinlock_unlock(&lock);
}

void* producer(void* args) {
  for (int i=0; i < NUM_ITERATIONS; i++)
    produce();
  return 0;
}
void* consumer(void* args) {
  for (int i=0; i< NUM_ITERATIONS; i++)
    consume();
  return 0;
}

int main (int argc, char** argv) {
  NUM_PRODUCERS = NUM_CONSUMERS = atoi(argv[1]);

  uthread_init(NUM_CONSUMERS + NUM_PRODUCERS);
  spinlock_create(&lock);
  uthread_t threads[NUM_PRODUCERS + NUM_CONSUMERS];
  for (int i = 0; i < NUM_PRODUCERS; i++) {
    threads[i] = uthread_create(producer, 0);
  }
  for (int i = NUM_PRODUCERS; i < (NUM_PRODUCERS + NUM_CONSUMERS); i++) {
    threads[i] = uthread_create(consumer, 0);
  } 
  // join threads
  for (int i = 0; i < NUM_PRODUCERS; i++) {
    uthread_join(threads[i], 0);
  }
  for (int i = NUM_PRODUCERS; i < (NUM_PRODUCERS + NUM_CONSUMERS); i++) {
    uthread_join(threads[i], 0);
  } 
  printf("Producer wait: %d\nConsumer wait: %d\n",
         producer_wait_count, consumer_wait_count);
  for(int i=0;i<MAX_ITEMS+1;i++)
    printf("items %d count %d\n", i, histogram[i]);
}