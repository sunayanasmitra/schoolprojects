#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char *data;
    int reference_bit;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct CircularQueue {
    Node *front;
    Node *rear;
    int size;
    int capacity;
    Node *pointer;
} CircularQueue;

CircularQueue *createCircularQueue(int capacity);
int isEmpty(CircularQueue *queue);
int isFull(CircularQueue *queue);
void enqueue(CircularQueue *queue, char *data, int reference_bit);
void dequeue(CircularQueue *queue);
bool existsInQueue(CircularQueue *queue, char *element);
bool search(CircularQueue *queue, char *element);
void displayQueue(CircularQueue *queue);
void destroyQueue(CircularQueue *queue);
