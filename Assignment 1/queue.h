#pragma once

#include <stdbool.h>

#include "user.h"

/// <summary>
/// A node from a linked list of users
/// </summary>
typedef struct queue_node {
    struct queue_node* next;
    user_t user;
} queue_node_t, *pqueue_node_t;

/// <summary>
/// A FIFO queues of users
/// </summary>
typedef struct queue {
    pqueue_node_t head;
    pqueue_node_t tail;
} *Queue;

/// <summary>
/// Creates an empty FIFO user queue
/// </summary>
Queue create_queue(void);

/// <summary>
/// Destroys a queue
/// </summary>
void destroy_queue(Queue queue);

/// <summary>
/// Checks if a queue is empty
/// </summary>
bool is_queue_empty(Queue queue);

/// <summary>
/// Adds a user to the tail of the queue
/// </summary>
bool enqueue(Queue queue, user_t user);

/// <summary>
/// Removes and returns the user at the head of the queue.
/// Make sure to check if a queue is empty before dequeuing.
/// </summary>
user_t dequeue(Queue queue);