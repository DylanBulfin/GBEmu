#include <stdio.h>
#include <time.h>
#include "waiting.h"

#define NANOSECS_PER_FRAME 16742706L

struct timespec end_time = {0,0};
struct timespec start_time = {0,0};

long timespec_diff(struct timespec *start, struct timespec *stop) {
  if(stop->tv_nsec < start->tv_nsec) {
    return (1000000000L + stop->tv_nsec) - start->tv_nsec;
  }
  return stop->tv_nsec - start->tv_nsec;
}

int timespec_comp(struct timespec *a, struct timespec *b) {
  if(a->tv_sec > b->tv_sec) {
    return 0;
  } else if(a->tv_sec < b->tv_sec) {
    return 1;
  } else {
    return (a->tv_nsec < b->tv_nsec);
  }
  return -1;
}

void timespec_add(struct timespec *ts, long nanosecs, struct timespec *res) {
  res->tv_nsec = (ts->tv_nsec + nanosecs) % 1000000000L;
  res->tv_sec = ts->tv_sec + ((ts->tv_nsec + nanosecs) > 1000000000L);
}
	

void pause_execution() {
  clock_gettime(CLOCK_MONOTONIC,&start_time);

  if(end_time.tv_sec == 0 && end_time.tv_nsec == 0) {
    end_time.tv_sec = start_time.tv_sec;
    end_time.tv_nsec = start_time.tv_nsec;
  } else {
    clock_gettime(CLOCK_MONOTONIC,&start_time);
  }

  long nanosecs_to_wait = NANOSECS_PER_FRAME - (timespec_diff(&end_time,&start_time));

  //    printf("Time taken: %ld, Time to wait: %ld\n", NANOSECS_PER_FRAME - nanosecs_to_wait, nanosecs_to_wait);

  struct timespec time_diff = {0,0};
  timespec_add(&start_time,nanosecs_to_wait,&time_diff);
    
  while(timespec_comp(&start_time,&time_diff)) {
    clock_gettime(CLOCK_MONOTONIC,&start_time);
  }

  clock_gettime(CLOCK_MONOTONIC,&end_time);
}
    
