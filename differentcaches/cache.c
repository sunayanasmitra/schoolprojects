#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "queue.h"
#include "List.h"
#include "clock.h"

#define BUFFER_SIZE 4096

queue_t *q;

int main(int argc, char **argv) {
    int cacheSize = 0;
    char policy = 'F';

    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Invalid command line arguments. Usage: ./cacher [-N <size>] <policy>\n");
        return 1;
    }

    if (argc == 2) {
        policy = argv[1][0];
    } else if (argc == 4) {
        if (strcmp(argv[1], "-N") == 0) {
            cacheSize = atoi(argv[2]);
            policy = argv[3][1];
        } else {
            fprintf(stderr, "Invalid command line argument.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid command line argument.\n");
        return 1;
    }

    //printf("%d %c\n", cacheSize, policy);

    char buffer[BUFFER_SIZE];
    char *input = NULL;
    size_t inputSize = 0;
    ssize_t bytesRead;

    int compulsoryMiss = 0;
    int capacityMiss = 0;

    while ((bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        char *temp = realloc(input, inputSize + bytesRead);
        input = temp;
        memcpy(input + inputSize, buffer, bytesRead);
        inputSize += bytesRead;
    }

    if (bytesRead == -1) {
        fprintf(stderr, "Error: Failed to read from stdin.\n");
        free(input);
        return 1;
    }

    char *token;

    if (policy == 'F') {
        List seen = newList();
        q = queue_new(cacheSize);

        token = strtok(input, "\n");
        while (token != NULL) {
            char *duplicate = strndup(token, strlen(token));

            if (in_queue(q, (void **) &duplicate) == true) {
                printf("HIT\n");
                free(duplicate);
            } else {
                if (ExistsInList(seen, duplicate) == 1) {
                    capacityMiss++;
                } else {
                    compulsoryMiss++;
                    append(seen, duplicate);
                }
                if (queue_is_full(q) == true) {
                    queue_pop(q);
                    queue_push(q, duplicate);
                    //capacityMiss++;
                } else {
                    queue_push(q, duplicate);
                    //compulsoryMiss++;
                }
                printf("MISS\n");
            }

            token = strtok(NULL, "\n");
        }
        freeList(&seen);
        queue_delete(&q);
        printf("%d %d\n", compulsoryMiss, capacityMiss);

    } else if (policy == 'L') {
        List seen = newList();
        List L = newList();
        token = strtok(input, "\n");
        while (token != NULL) {
            char *duplicate = strndup(token, strlen(token));

            if (ExistsInList(L, duplicate) == 1) {
                printf("HIT\n");
                moveFront(L);
                while (indx(L) >= 0) {
                    if (strcmp(duplicate, get(L)) == 0) {
                        delete (L);
                        append(L, duplicate);
                    }
                    moveNext(L);
                }
                //free(duplicate);
            } else {
                char *dup2 = strndup(token, strlen(token));
                if (ExistsInList(seen, dup2) == 1) {
                    capacityMiss++;
                } else {
                    compulsoryMiss++;
                    append(seen, dup2);
                }
                //free(dup2);
                if (length(L) == cacheSize) {
                    deleteFront(L);
                    append(L, duplicate);
                } else {
                    append(L, duplicate);
                }
                printf("MISS\n");
            }
            token = strtok(NULL, "\n");
        }
        freeList(&L);
        freeList(&seen);
        printf("%d %d\n", compulsoryMiss, capacityMiss);
    } else if (policy == 'C') {
        List seen = newList();
        CircularQueue *queue = createCircularQueue(cacheSize);
        token = strtok(input, "\n");
        while (token != NULL) {
            char *duplicate = strndup(token, strlen(token));
            if (search(queue, duplicate) == true) {
                printf("HIT\n");
            } else {
                char *dup2 = strndup(token, strlen(token));
                if (ExistsInList(seen, dup2) == 1) {
                    capacityMiss++;
                } else {
                    compulsoryMiss++;
                    append(seen, dup2);
                }
                enqueue(queue, duplicate, 0);

                printf("MISS\n");
            }
            token = strtok(NULL, "\n");
        }

        freeList(&seen);
        destroyQueue(queue);
        printf("%d %d\n", compulsoryMiss, capacityMiss);
    } else {
        fprintf(stderr, "Invalid policy.\n");
        return 1;
    }

    free(input);

    return 0;
}
