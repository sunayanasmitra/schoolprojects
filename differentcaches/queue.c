#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include "queue.h"

struct node {
    struct node *next;
    void *data;
    struct node *prev;
};

struct queue {
    struct node *front;
    struct node *back;
    int size;
    int length;
    pthread_mutex_t mutex;
};

queue_t *queue_new(int size) {
    queue_t *q = malloc(sizeof(queue_t));
    q->front = NULL;
    q->back = NULL;
    q->size = size;
    q->length = 0;
    pthread_mutex_init(&(q->mutex), NULL);
    return q;
}

void queue_delete(queue_t **q) {
    if (*q == NULL) {
        return;
    }

    pthread_mutex_lock(&((*q)->mutex));

    struct node *current = (*q)->front;
    while (current != NULL) {
        struct node *temp = current;
        current = current->next;
        free(temp);
    }

    pthread_mutex_unlock(&((*q)->mutex));
    pthread_mutex_destroy(&((*q)->mutex));

    free(*q);
    *q = NULL;
}

bool queue_push(queue_t *q, void *elem) {
    if (q == NULL) {
        return false;
    }

    pthread_mutex_lock(&(q->mutex));

    if (q->length == q->size) {
        pthread_mutex_unlock(&(q->mutex));
        return false;
    }

    struct node *temp = malloc(sizeof(struct node));
    temp->data = elem;
    temp->next = q->front;
    temp->prev = NULL;

    if (q->back == NULL) {
        q->back = temp;
    }

    if (q->front != NULL) {
        q->front->prev = temp;
    }

    q->front = temp;
    q->length++;

    pthread_mutex_unlock(&(q->mutex));

    return true;
}

bool queue_pop(queue_t *q) {
    if (q == NULL || q->back == NULL) {
        return false;
    }

    pthread_mutex_lock(&(q->mutex));

    struct node *temp = q->back;
    q->back = temp->prev;

    if (q->back == NULL) {
        q->front = NULL;
    } else {
        q->back->next = NULL;
    }

    free(temp);
    q->length--;

    pthread_mutex_unlock(&(q->mutex));

    return true;
}

bool in_queue(queue_t *q, void **elem) {
    if (q == NULL || q->front == NULL) {
        return false;
    }

    pthread_mutex_lock(&(q->mutex));

    struct node *current = q->front;
    while (current != NULL) {
        if (strcmp((char *) current->data, (char *) *elem) == 0) {
            pthread_mutex_unlock(&(q->mutex));
            return true;
        }
        current = current->next;
    }

    pthread_mutex_unlock(&(q->mutex));
    return false;
}

bool queue_is_full(queue_t *q) {
    if (q == NULL) {
        return false;
    }

    pthread_mutex_lock(&(q->mutex));

    bool isFull = (q->length == q->size);

    pthread_mutex_unlock(&(q->mutex));

    return isFull;
}
