/*
 *  test.c
 *
 *  copyright (c) 2019-2021 Xiongfei Shi
 *
 *  author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
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

  printf("2000yr is leap year? %d\n", hrisleapyear(2000));
  printf("2011yr is leap year? %d\n", hrisleapyear(2011));

  printf("2000-02 days in month: %d\n", hrdaysinmonth(2000, 2));
  printf("2011-02 days in month: %d\n", hrdaysinmonth(2011, 2));

  printf("2000-10-10 year day is: %d\n", hryearday(2000, 10, 10));
  printf("2011-10-10 year day is: %d\n", hryearday(2011, 10, 10));

  return 0;
}
