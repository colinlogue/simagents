#include <stdlib.h>

typedef struct queue_node {
  struct queue_node *next;
  void *content;
  size_t content_size;
} queue_node_t;

typedef struct {
  queue_node_t *head;
  queue_node_t *tail;
  int len;
} queue_t;

queue_t *q_create() {
  queue_t *q = malloc(sizeof(queue_t));
  q->len = 0;
  q->head = NULL;
  q->tail = NULL;
  return q;
};

void q_append(queue_t *q, void *next_ptr, size_t next_size) {
  // create queue item for new tail
  queue_node_t *new_tail = malloc(sizeof(queue_node_t));
  new_tail->content = next_ptr;
  new_tail->content_size = next_size;
  new_tail->next = NULL;

  // update queue
  if (q->tail) q->tail->next = new_tail; else q->head = new_tail;
  q->tail = new_tail;
  q->len++;
};

void q_clear(queue_t *q) {
  queue_node_t *node = q->head;
  while (q->tail) {
  	q->head = node;
  	node = node->next;
  	free(q->head);
    if (q->tail == node) {
      q->tail = NULL;
    }
  }
  q->len = 0;
};

queue_node_t *q_get_nth(queue_t *q, int n) {
  // 0-indexed
  queue_node_t *node = q->head;
  for (int i = 0; i < n; i++) {
    node = node->next;
  }
  return node;
};