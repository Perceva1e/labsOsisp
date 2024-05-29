
#include <stddef.h>
#include <signal.h>

#include <sys/time.h>


enum child {
  CHILD_ASK,
  CHILD_INFORM,
};
enum parent {
  PARENT_KILL,
  PARENT_FORCE_PRINT,
  PARENT_RESPONSE,
};

#define ALARM_COUNTS_TO_PRINT 101
#define ALARM_DELAY 30000  

typedef struct {
  int O;
  int I;
} binary_t;

typedef struct {
  size_t O_O;
  size_t O_I;
  size_t I_O;
  size_t I_I;
} stat_t;

void init(struct itimerval* timer);

void alarm_handler(int sig);
void parent_handler(int sig, siginfo_t* info, void* context);
void atexit_handler(void);

void ask_to_print(void);
void inform_about_print(void);

void print_stat(void);

void reset_cycle(void);
