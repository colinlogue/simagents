#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_node {
  struct queue_node *next;
  void *content;
} queue_node_t;

typedef struct queue {
  queue_node_t *head;
  queue_node_t *tail;
  size_t len;
} queue_t;

// functions
queue_t *q_create();
void q_append(queue_t*, void*, size_t);
void q_clear(queue_t*);
queue_node_t *q_get_nth(queue_t*, int);

#endif