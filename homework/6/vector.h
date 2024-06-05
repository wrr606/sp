#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <pthread.h>
#include "net.h"

typedef struct {
    pthread_t thread;
    int id;
} T;

typedef struct {
    T *data;
    size_t size;
    size_t capacity;
} Vector_t;

Vector_t vector_create();
void vector_push_back(Vector_t *vec, int value);

#endif // VECTOR_H