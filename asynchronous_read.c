#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <assert.h>
#include "uthread.h"
#include "queue.h"
#include "disk.h"

int sum = 0;

/**
 * Read a given number of disk blocks and sum the values contained in the block asynchronously
 */


struct PendingRead {
  char* aBuf;
  int aSiz;
  int blockno; 
  void (*handler) (char*, int, int);
} ;

/**
 * Queue of pending reads.
 */
queue_t prq;
struct PendingRead* pr;

void interruptServiceRoutine (){
  struct PendingRead* pr = queue_dequeue(&prq);
  pr->handler(pr->aBuf, pr->aSiz, pr->blockno);

}

void asyncRead (char* buf, int nbytes, int blockno, void (*handler) (char*, int, int)) {
  pr->aBuf = buf;
  pr->aSiz = nbytes;
  pr->blockno = blockno;
  pr->handler = handler;
  disk_scheduleRead(buf, nbytes, blockno);

}


void handleRead (char* buf, int nbytes, int blockno) {
  assert (*((int*)buf) == blockno);
  //printf ("buf = %d, blockno = %d\n", *((int*) buf), blockno);
  sum += *(((int*) buf) + 1);
}

/**
 * Read numBlocks blocks from disk sequentially starting at block 0.
 */
void run (int numBlocks) {
  for (int blockno = 0; blockno < numBlocks; blockno++) {
    char* buf = malloc(4096);
    pr = malloc(sizeof(struct PendingRead));
    queue_enqueue(&prq, pr);
    asyncRead(buf, sizeof(buf), blockno, handleRead);
  }
  disk_waitForReads();
}

int main (int argc, char** argv) {
  static const char* usage = "usage: aRead numBlocks";
  int numBlocks = 0;
  queue_init(&prq);
  
  if (argc == 2)
    numBlocks = strtol (argv [1], NULL, 10);
  if (argc != 2 || (numBlocks == 0 && errno == EINVAL)) {
    printf ("%s\n", usage);
    return EXIT_FAILURE;
  }
  
  uthread_init (1);
  disk_start   (interruptServiceRoutine);
  
  run (numBlocks);
  
  printf ("%d\n", sum);
}