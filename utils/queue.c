#include <stdlib.h>
#include "queue.h"

queue_t *q_create() {
/**
  * Creates and initializes a new queue.
  *
  * Returns
  * -------
  * q : *queue_t
  *     Pointer to the newly created queue.
**/
  queue_t *q = malloc(sizeof(queue_t));
  q->len = 0;
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void q_destroy(queue_t *q) {
/**
  * Frees memory for the queue and all its nodes.
  *
  * Parameters
  * ----------
  * q : *queue_t
  *     Pointer to the queue to be destroyed.
**/
  q_clear(q);
  free(q);
}

queue_node_t *q_append(queue_t *q, void *content) {
/**
  * Adds a new node to the end of the queue.
  *
  * Parameters
  * ----------
  * q : *queue_t
  *     Pointer to the queue to append the new node to.
  * content : *void
  *     Pointer to be set as the content value of the new node.
  *
  * Returns
  * -------
  * new_tail : *queue_node_t
  *     Pointer to the newly appended node.
**/

  // create new queue node
  queue_node_t *new_tail = malloc(sizeof(queue_node_t));
  new_tail->content = content;
  new_tail->next = NULL;

  // update queue
  if (q->tail) q->tail->next = new_tail; else q->head = new_tail;
  q->tail = new_tail;
  q->len++;

  return new_tail;
}

queue_node_t *q_insert_at(queue_t *q, void *content, size_t idx) {
/**
  * Inserts a new node at the given index.
  *
  * Parameters
  * ----------
  * q : *queue_t
  *     Pointer to the queue to insert the node into.
  * content : *void
  *     Pointer to be set as the content value for the new node.
  * idx : size_t
  *     Point of insertion for new node.
  *
  * Returns
  * -------
  * node : *queue_node_t
  *     Pointer to inserted node.
**/

  // create new node
  queue_node_t *node = malloc(sizeof(queue_node_t));
  node->content = content;

  // get previous and displaced nodes
  queue_node_t *previous_node;
  queue_node_t *displaced_node;
  if (idx == 0) {
    previous_node = NULL;
    displaced_node = q->head;
  }
  else {
    previous_node = q_get_nth(q, idx - 1);
    if (!previous_node) {
      // if no node at idx - 1 in queue, exit with error
      fprintf(stderr, "Can't insert into queue at index %i", idx);
      exit(EXIT_FAILURE);
    }
    displaced_node = previous_node->next;
    previous_node->next = node;
  }
  node->next = displaced_node;

  // update queue
  if (!previous_node) q->head = node;
  if (!displaced_node) q->tail = node;
  q->len++;
  
  return node;
}

void q_delete_at(queue_t *q, size_t idx) {
/**
  * Deletes the node at the given index of the given queue.
  *
  * Parameters
  * ----------
  * q : *queue_t
  *     Pointer to the queue from which to delete the node.
  * idx : size_t
  *     Index of the node to be deleted.
**/
  queue_node_t *previous_node, *deletion_node, *following_node;
  
  if (idx == 0) {
    previous_node = NULL;
    deletion_node = q->head;
    following_node = deletion_node->next;
    q->head = following_node;
  }
  else {
    previous_node = q_get_nth(q, idx - 1);
    deletion_node = previous_node->next;
    following_node = deletion_node->next;
    previous_node->next = following_node;
  }

  free(deletion_node);

  // update queue
  if (!following_node) q->tail = previous_node;
  q->len--;
}

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
}

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
}