#include <stdlib.h>
#include "queue.h"

queue_t *q_create() {
/**
  * 
**/
  queue_t *q = malloc(sizeof(queue_t));
  q->len = 0;
  q->head = NULL;
  q->tail = NULL;
  return q;
};

void q_append(queue_t *q, void *next_ptr, char next_type) {
/**
  * Adds a new item to the end of the queue.
  *
  * Parameters
  * ----------
  * q : *queue_t
  *     Pointer to the queue to append the 
**/

  // create new queue node
  queue_node_t *new_tail = malloc(sizeof(queue_node_t));
  new_tail->content = next_ptr;
  new_tail->content_type = next_tye;
  new_tail->next = NULL;

  // update queue
  if (q->tail) q->tail->next = new_tail; else q->head = new_tail;
  q->tail = new_tail;
  q->len++;
};

void q_clear(queue_t *q) {
/**
  * Deletes and frees allocated memory for each node in the queue.
  *
  * Parameters
  * ----------
  * q : *queue_t
  *     Pointer to the queue to be cleared.
**/
  queue_node_t *node = q->head;
  while (q->tail) {
  	q->head = node;
  	node = node->next;
  	free(q->head);
    if (q->tail == node) {
      free(node);
      q->tail = NULL;
    }
  }
  q->len = 0;
};

queue_node_t *q_get_nth(queue_t *q, size_t n) {
/**
  * Traverses the queue to find the nth node. Zero-indexed.
  *
  * Parameters
  * ----------
  * q : *queue_t
  *     Pointer to the queue to search.
  * n : size_t
  *     Index of the node being searched for.
  *
  * Returns
  * -------
  * node : *queue_node_t
  *     Pointer to the node at position n in queue q, or NULL if n is greater
  *     than the length of the queue.
**/

  // check if n is greater than length of queue
  if (n >= q-> len) {
    return NULL;
  }
  // traverse queue until node n
  queue_node_t *node = q->head;
  for (int i = 0; i < n; i++) {
    node = node->next;
  }
  return node;
};