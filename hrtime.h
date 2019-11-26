/*
 *  hrtime.h
 *
 *  copyright (c) 2019 Xiongfei Shi
 *
 *  author: Xiongfei Shi <jenson.shixf(a)gmail.com>
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

#ifdef __cplusplus
};
#endif

#endif /* __HRTIME_H__ */
