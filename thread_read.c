#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <assert.h>
#include "queue.h"
#include "disk.h"
#include "uthread.h"

/**
 * Read a given number of disk blocks and sum the values contained in the block using threads
 */

int sum = 0;
queue_t prq;

void interruptServiceRoutine () {
  uthread_t t = queue_dequeue(&prq);
  uthread_unblock(t);
}

void blockUntilComplete() {
  queue_enqueue(&prq, uthread_self());
  uthread_block(uthread_self());
}

void handleRead (char* buf, int nbytes, int blockno) {
  //printf ("buf = %d, blockno = %d\n", *((int*) buf), blockno);
  assert (*((int*)buf) == blockno);
  sum += *(((int*) buf) + 1);
}

/**
 * Struct provided as argument to readAndHandleBlock
 */
struct readAndHandleBlockArgs {
  char* buf;
  int   nbytes;
  int   blockno;
};

void* readAndHandleBlock (void* args_voidstar) {
  struct readAndHandleBlockArgs* blk = (struct readAndHandleBlockArgs*) args_voidstar;
  disk_scheduleRead(blk->buf, blk->nbytes, blk->blockno);
  blockUntilComplete();
  handleRead(blk->buf, blk->nbytes, blk->blockno);
  return blk->buf;
}

void run (int numBlocks) {
  uthread_t thread [numBlocks];
  
  for (int blockno = 0; blockno < numBlocks; blockno++) {
    char* buf = malloc(4096);
    struct readAndHandleBlockArgs* blk = malloc(sizeof(struct readAndHandleBlockArgs));
    blk->buf = buf;
    blk->nbytes = sizeof(buf);
    blk->blockno = blockno;
    thread[blockno] = uthread_create(readAndHandleBlock, blk);
  }
  disk_waitForReads();
  printf("read complete\n");
  for (int i=0; i<numBlocks; i++) {
    uthread_join (thread [i], 0);
  }

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