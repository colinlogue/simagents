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
queue_node_t *q_append(queue_t *, void *);
queue_node_t *q_get_nth(queue_t *, size_t);
queue_node_t *q_insert_at(queue_t *, void *, size_t);
void q_destroy(queue_t *);
void q_delete_at(queue_t *, size_t);
void q_clear(queue_t *);

#endif