#include "vector.h"

#define INITIAL_CAPACITY 10

Vector_t vector_create() {
    Vector_t vec;
    vec.data = (T*)malloc(INITIAL_CAPACITY * sizeof(T));
    vec.size = 0,vec.capacity = INITIAL_CAPACITY;
    return vec;
}

void vector_push_back(Vector_t *vec, int value) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        vec->data = (T*)realloc(vec->data, vec->capacity * sizeof(T));
        if (vec->data == NULL)
            return;
    }
    vec->data[vec->size++].id = value;
}