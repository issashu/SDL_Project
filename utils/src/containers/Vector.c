//Corresponding header
#include "utils/containers/Vector.h"

//C system headers
#include <stdlib.h>

//Other libraries headers

//Own components headers

void initVector(struct Vector *vec, size_t initialCapacity) {
  vec->capacity = initialCapacity;
  vec->size = 0;

  if (0 != initialCapacity) {
    vec->items = malloc(sizeof(void*) * vec->capacity);
  } else {
    vec->items = NULL;
  }
}

size_t getSizeVector(const struct Vector *v) {
  return v->size;
}

bool isEmptyVector(const struct Vector *vec) {
  return vec->size == 0;
}

void resizeVector(struct Vector *vec, size_t newSize) {
  //memory is still kept reserved even if the size shrinks
  if (newSize <= vec->size) {
    vec->size = newSize;
    return;
  }

  void **items = realloc(vec->items, sizeof(void*) * newSize);
  if (items) {
    vec->items = items;
    vec->capacity = newSize;
    vec->size = newSize;
  }
}

void reserveVector(struct Vector *vec, size_t newCapacity) {
  void **items = realloc(vec->items, sizeof(void*) * newCapacity);
  if (items) {
    vec->items = items;
    vec->capacity = newCapacity;

    //shrink elements if needed
    if (newCapacity < vec->size) {
      vec->size = newCapacity;
    }
  }
}

void pushElementVector(struct Vector *vec, void *item) {
  if (0 == vec->capacity) {
    reserveVector(vec, 1);
  }
  else if (vec->capacity == vec->size) {
    reserveVector(vec, vec->capacity * 2);
  }
  vec->items[vec->size] = item;
  vec->size++;
}

void setElementVector(struct Vector *vec, size_t idx, void *item) {
  if (idx < vec->size) {
    vec->items[idx] = item;
  }
}

void* getElementVector(const struct Vector *vec, size_t idx) {
  if (idx < vec->size) {
    return vec->items[idx];
  }
  return NULL;
}

void* backElementVector(struct Vector *vec) {
  if (0 == vec->size) {
    return NULL;
  }

  return vec->items[vec->size - 1];
}

void deleteElementVector(struct Vector *vec, size_t idx) {
  if (idx >= vec->size) {
    return;
  }

  vec->items[idx] = NULL;

  for (size_t i = idx; i < vec->size - 1; ++i) {
      vec->items[i] = vec->items[i + 1];
      vec->items[i + 1] = NULL;
  }

  vec->size--;
}

void popElementVector(struct Vector *vec) {
  if (vec->size == 0) {
    return;
  }

  vec->size--;
}

void clearElementsVector(struct Vector *vec) {
  resizeVector(vec, 0);
}

void shrinkToFitVector(struct Vector *vec) {
  if (vec->capacity >= vec->size) {
    return;
  }

  void **items = realloc(vec->items, sizeof(void*) * vec->capacity);
  if (items) {
    vec->items = items;
    vec->size = vec->capacity;
  }
}

void deepCopyVector(const struct Vector *from, struct Vector *to) {
  to->size = from->size;
  to->capacity = from->capacity;
  if (NULL != from->items) {
    to->items = malloc(sizeof(void*) * from->capacity);
    for (size_t i = 0; i < to->capacity; ++i) {
      to->items[i] = from->items[i];
    }
  }
}

void freeVector(struct Vector *vec) {
  if (vec->items != NULL) {
    free(vec->items);
    vec->items = NULL;
    vec->size = 0;
    vec->capacity = 0;
  }
}

