#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "queue.h"

Queue create_queue(void) {
    Queue queue = (Queue)malloc(sizeof(struct queue));
    if (!queue) {
        fprintf(stderr, "Error: Failed to allocate new queue.\n");
        exit(EXIT_FAILURE);
    }

    // Init to empty
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

void destroy_queue(Queue queue) {
    // Destroy each node
    pqueue_node_t current = queue->head; 
    while (current != NULL) {
       pqueue_node_t temp = current->next;
       free(current);
       current = temp;
    }

    free(queue);
}

bool is_queue_empty(Queue queue) {
    return queue->head == NULL;
}

bool enqueue(Queue queue, user_t user) {
    pqueue_node_t node = (pqueue_node_t)malloc(sizeof(queue_node_t));
    if (!node) {
        fprintf(stderr, "Error: Failed to allocate new queue node.\n");
        return false;
    }

    node->user = user;
    node->next = NULL;

    // Queue is empty, head and tail become new node
    if (queue->head == NULL) {
        assert(queue->tail == NULL);
        
        queue->head = node;
        queue->tail = node;
        return true;
    }
    
    // Queue has contents, point the tail to the new node and set the tail
    queue->tail->next = node;
    queue->tail = node;
    return true;
}

user_t dequeue(Queue queue) {
    if (is_queue_empty(queue)) {
        fprintf(stderr, "Error: Tried to dequeue from an empty queue.\n");
        exit(EXIT_FAILURE);
    }

    user_t user = queue->head->user;

    // Queue has only one item
    if (queue->head == queue->tail) {
        assert(queue->head->next == NULL);

        free(queue->head);
        queue->head = NULL;
        queue->tail = NULL;
        
        return user;
    }

    // Queue has more than one item
    assert(queue->head->next != NULL);

    pqueue_node_t temp = queue->head->next;
    free(queue->head);
    queue->head = temp;
    
    return user;
}