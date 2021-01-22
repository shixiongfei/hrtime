/*
 *  hrtime.h
 *
 *  copyright (c) 2019-2021 Xiongfei Shi
 *
 *  author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 *  license: Apache-2.0
 *
 *  https://github.com/shixiongfei/hrtime
 */

#ifndef __HRTIME_H__
#define __HRTIME_H__

#ifdef __cplusplus
extern "C" {
#endif

void hrperiod(int enable);
double hrtime(long *sec, long *usec);
void hrdelay(double seconds);
double hrclock(void);
int hrtimezone(void);
int hrisleapyear(int year);
int hrdaysinmonth(int year, int month);
int hryearday(int year, int month, int day);

#ifdef __cplusplus
};
#endif

#endif /* __HRTIME_H__ */
