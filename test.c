/*
 *  test.c
 *
 *  copyright (c) 2019 Xiongfei Shi
 *
 *  author: Xiongfei Shi <jenson.shixf(a)gmail.com>
 *  license: Apache-2.0
 *
 *  https://github.com/shixiongfei/hrtime
 */

#include "hrtime.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  long sec, usec;
  double start, stop;

  hrperiod(1);

  printf("time zone = %d\n", hrtimezone());
  printf("hrtime = %lf\n", hrtime(&sec, &usec));
  printf("sec = %ld, usec = %ld\n", sec, usec);

  start = hrclock();
  hrdelay(1.5);
  stop = hrclock();

  printf("start = %lf, stop = %lf, delay = %lf\n", start, stop, stop - start);

  return 0;
}
