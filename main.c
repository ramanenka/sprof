#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>

// 38.37s user 0.07s system 389% cpu 9.870 total

// 2953

// 38370000 + 70000 = 38440000

// 38440000 / 2953 = 13017
//                   10000


void* work(void *arg) {
  uint64_t tid;
  pthread_threadid_np(NULL, &tid);
  for (int i = 0; i < 10; i++) {
    printf("%llu: working...\n", tid);
    int l = ((rand() % 5) * 10000000);
    for (int j = 0; j < l; j++) {
      long d = exp(j * 123.123) * sin(j * 123.123);
    }
  }

  return NULL;
}

static void prof_handler(int sig) {
  uint64_t tid;
  pthread_threadid_np(NULL, &tid);
  printf("signal received: %d, tid: %llu\n", sig, tid);
}

int main() {
  uint64_t tid;
  pthread_threadid_np(NULL, &tid);
  printf("main tid: %llu\n", tid);

  struct sigaction act;
  memset (&act, '\0', sizeof(act));
  act.sa_handler = &prof_handler;
  sigemptyset(&act.sa_mask);
  if (sigaction(SIGPROF, &act, NULL) < 0) {
    printf("register signal error");
    return 1;
  }

  static struct itimerval timer;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 1000000/100;
  timer.it_value = timer.it_interval;
  if (setitimer(ITIMER_PROF, &timer, NULL) != 0) {
    printf("settimer failed");
    return 1;
  }

  pthread_t pts[5];
  for (int i = 0; i < 5; i++) {
    int result_code = pthread_create(&pts[i], NULL, work, NULL);
    if (result_code) {
      printf("create %d thread: %d", i, result_code);
      return 1;
    }
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(pts[i], NULL);
  }

  return 0;
}

