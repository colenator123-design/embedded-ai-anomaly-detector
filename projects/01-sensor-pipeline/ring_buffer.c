#include "ring_buffer.h"

int float_ring_buffer_init(float_ring_buffer_t *rb, float *storage, size_t capacity)
{
    if (rb == 0 || storage == 0 || capacity == 0) {
        return -1;
    }

    rb->buffer = storage;
    rb->capacity = capacity;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
    return 0;
}

int float_ring_buffer_push(float_ring_buffer_t *rb, float value)
{
    if (rb == 0) {
        return -1;
    }

    if (float_ring_buffer_is_full(rb)) {
        rb->buffer[rb->head] = value;
        rb->head = (rb->head + 1) % rb->capacity;
        rb->tail = rb->head;
        return 0;
    }

    rb->buffer[rb->head] = value;
    rb->head = (rb->head + 1) % rb->capacity;
    rb->count++;
    return 0;
}

int float_ring_buffer_pop(float_ring_buffer_t *rb, float *value)
{
    if (rb == 0 || value == 0 || float_ring_buffer_is_empty(rb)) {
        return -1;
    }

    *value = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->count--;
    return 0;
}

int float_ring_buffer_is_empty(const float_ring_buffer_t *rb)
{
    return rb == 0 || rb->count == 0;
}

int float_ring_buffer_is_full(const float_ring_buffer_t *rb)
{
    return rb != 0 && rb->count == rb->capacity;
}

size_t float_ring_buffer_size(const float_ring_buffer_t *rb)
{
    if (rb == 0) {
        return 0;
    }
    return rb->count;
}
