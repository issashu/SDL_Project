#ifndef UTILS_LOG_H_
#define UTILS_LOG_H_

// C system headers
#include <stdarg.h>
#include <stdio.h>

// Other libraries headers

// Own components headers

/* terminal colors */
#define TERM_BOLD "\033[1m "
#define TERM_RED "\033[31m"
#define TERM_GREEN "\033[32m"
#define TERM_YELLOW "\033[33m"
#define TERM_BLUE "\033[34m"
#define TERM_MAGENTA "\033[35m"
#define TERM_CYAN "\033[36m"
#define TERM_COLOR_NONE "\033[0m"

#define LOGERR(format, ...)                                         \
  do {                                                              \
    printf(TERM_BOLD TERM_RED);                                     \
    printf("%s(%s:%d): " format "\n", __func__, __FILE__, __LINE__, \
           ##__VA_ARGS__);                                          \
    printf(TERM_COLOR_NONE);                                        \
    fflush(stdout);                                                 \
  } while (0);

#define LOG(format, ...)                \
  do {                                  \
    printf(format "\n", ##__VA_ARGS__); \
    fflush(stdout);                     \
  } while (0);

#define LOG_ON_SAME_LINE(format, ...) \
  do {                                \
    printf(format, ##__VA_ARGS__);    \
    fflush(stdout);                   \
  } while (0);

#define LOGG(format, ...)               \
  do {                                  \
    printf(TERM_GREEN);                 \
    printf(format "\n", ##__VA_ARGS__); \
    printf(TERM_COLOR_NONE);            \
    fflush(stdout);                     \
  } while (0);

#define LOGG_ON_SAME_LINE(format, ...) \
  do {                                 \
    printf(TERM_GREEN);                \
    printf(format, ##__VA_ARGS__);     \
    printf(TERM_COLOR_NONE);           \
    fflush(stdout);                    \
  } while (0);

#define LOGY(format, ...)               \
  do {                                  \
    printf(TERM_YELLOW);                \
    printf(format "\n", ##__VA_ARGS__); \
    printf(TERM_COLOR_NONE);            \
    fflush(stdout);                     \
  } while (0);

#define LOGY_ON_SAME_LINE(format, ...) \
  do {                                 \
    printf(TERM_YELLOW);               \
    printf(format, ##__VA_ARGS__);     \
    printf(TERM_COLOR_NONE);           \
    fflush(stdout);                    \
  } while (0);

#define LOGB(format, ...)               \
  do {                                  \
    printf(TERM_BLUE);                  \
    printf(format "\n", ##__VA_ARGS__); \
    printf(TERM_COLOR_NONE);            \
    fflush(stdout);                     \
  } while (0);

#define LOGB_ON_SAME_LINE(format, ...) \
  do {                                 \
    printf(TERM_BLUE);                 \
    printf(format, ##__VA_ARGS__);     \
    printf(TERM_COLOR_NONE);           \
    fflush(stdout);                    \
  } while (0);

#define LOGM(format, ...)               \
  do {                                  \
    printf(TERM_MAGENTA);               \
    printf(format "\n", ##__VA_ARGS__); \
    printf(TERM_COLOR_NONE);            \
    fflush(stdout);                     \
  } while (0);

#define LOGM_ON_SAME_LINE(format, ...) \
  do {                                 \
    printf(TERM_MAGENTA);              \
    printf(format, ##__VA_ARGS__);     \
    printf(TERM_COLOR_NONE);           \
    fflush(stdout);                    \
  } while (0);

#define LOGC(format, ...)               \
  do {                                  \
    printf(TERM_CYAN);                  \
    printf(format "\n", ##__VA_ARGS__); \
    printf(TERM_COLOR_NONE);            \
    fflush(stdout);                     \
  } while (0);

#define LOGC_ON_SAME_LINE(format, ...) \
  do {                                 \
    printf(TERM_CYAN);                 \
    printf(format, ##__VA_ARGS__);     \
    printf(TERM_COLOR_NONE);           \
    fflush(stdout);                    \
  } while (0);

#define LOGR(format, ...)               \
  do {                                  \
    printf(TERM_RED);                   \
    printf(format "\n", ##__VA_ARGS__); \
    printf(TERM_COLOR_NONE);            \
    fflush(stdout);                     \
  } while (0);

#define LOGR_ON_SAME_LINE(format, ...) \
  do {                                 \
    printf(TERM_RED);                  \
    printf(format, ##__VA_ARGS__);     \
    printf(TERM_COLOR_NONE);           \
    fflush(stdout);                    \
  } while (0);

#endif /* UTILS_LOG_H_ */
