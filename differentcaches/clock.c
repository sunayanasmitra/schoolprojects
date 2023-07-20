#include <stdio.h>
#include <stdlib.h>

#include "clock.h"

CircularQueue *createCircularQueue(int capacity) {
    CircularQueue *queue = (CircularQueue *) malloc(sizeof(CircularQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    queue->capacity = capacity;
    queue->pointer = NULL;
    return queue;
}

int isEmpty(CircularQueue *queue) {
    return (queue->size == 0);
}

int isFull(CircularQueue *queue) {
    return (queue->size == queue->capacity);
}

void enqueue(CircularQueue *queue, char *data, int reference_bit) {
    if (isFull(queue)) {
        while (queue->pointer->reference_bit != 0) {
            queue->pointer->reference_bit = 0;
            queue->pointer = queue->pointer->next;
        }

        Node *temp = queue->pointer;
        temp->data = data;
        temp->reference_bit = reference_bit;

        queue->pointer = queue->pointer->next;

        /*while (queue->pointer != temp) {
            queue->pointer->reference_bit = 0;
            queue->pointer = queue->pointer->next;
        }*/
    } else {
        Node *newNode = (Node *) malloc(sizeof(Node));
        newNode->data = data;
        newNode->reference_bit = reference_bit;

        if (isEmpty(queue)) {
            queue->front = newNode;
            queue->rear = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
            queue->pointer = newNode;
        } else {
            newNode->next = queue->front;
            newNode->prev = queue->rear;
            queue->rear->next = newNode;
            queue->front->prev = newNode;
            queue->rear = newNode;
        }

        queue->size++;
    }
}

void dequeue(CircularQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    if (queue->size == 1) {
        free(queue->front);
        queue->front = NULL;
        queue->rear = NULL;
        queue->pointer = NULL;
    } else {
        Node *temp = queue->front;
        queue->front = queue->front->next;
        queue->front->prev = queue->rear;
        queue->rear->next = queue->front;
        queue->pointer = queue->front;
        free(temp);
    }

    queue->size--;
}

bool existsInQueue(CircularQueue *queue, char *element) {
    if (isEmpty(queue)) {
        return false;
    }

    Node *current = queue->front;
    while (current != queue->rear) {
        if (strcmp(current->data, element) == 0) {
            return true;
        }
        current = current->next;
    }

    if (strcmp(current->data, element) == 0) {
        return true;
    }

    return false;
}

bool search(CircularQueue *queue, char *element) {
    if (isEmpty(queue)) {
        return false;
    }

    Node *current = queue->front;
    while (current != queue->rear) {
        if (strcmp(current->data, element) == 0) {
            current->reference_bit = 1;
            return true;
        }
        current = current->next;
    }

    if (strcmp(current->data, element) == 0) {
        current->reference_bit = 1;
        return true;
    }

    return false;
}

void displayQueue(CircularQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    Node *current = queue->front;
    printf("Circular Queue: ");
    do {
        printf("(%s, %d) ", current->data, current->reference_bit);
        current = current->next;
    } while (current != queue->front);
    printf("\n");
}

void destroyQueue(CircularQueue *queue) {
    if (isEmpty(queue)) {
        free(queue);
        return;
    }

    Node *current = queue->front;
    Node *next;

    while (current != queue->rear) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(queue->rear);
    free(queue);
}
