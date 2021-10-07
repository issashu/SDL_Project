#ifndef UTILS_CONTAINERS_VECTOR_H_
#define UTILS_CONTAINERS_VECTOR_H_

// C system headers
#include <stddef.h>
#include <stdbool.h>

// Other libraries headers

// Own components headers

// Forward declarations

struct Vector {
  void **items;
  size_t capacity;
  size_t size;
};

void initVector(struct Vector *vec, size_t initialCapacity);
size_t getSizeVector(const struct Vector *vec);
bool isEmptyVector(const struct Vector *vec);
void resizeVector(struct Vector *vec, size_t newSize);
void reserveVector(struct Vector *vec, size_t newCapacity);
void pushElementVector(struct Vector *vec, void *elem);
void setElementVector(struct Vector *vec, size_t idx, void *elem);
void* getElementVector(const struct Vector *vec, size_t idx);
void* backElementVector(struct Vector *vec);
void deleteElementVector(struct Vector *vec, size_t idx);
void popElementVector(struct Vector *vec);
void clearElementsVector(struct Vector *vec);
void shrinkToFitVector(struct Vector *vec);
void deepCopyVector(const struct Vector *from, struct Vector *to);
void freeVector(struct Vector *vec);

#endif /* UTILS_CONTAINERS_VECTOR_H_ */

