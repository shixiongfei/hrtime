/*
 *  hrtime.c
 *
 *  copyright (c) 2019-2021 Xiongfei Shi
 *
 *  author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 *  license: Apache-2.0
 *
 *  https://github.com/shixiongfei/hrtime
 */

#ifdef _WIN32
#include <WinSock2.h> /* struct timeval */
#include <mmsystem.h> /* timeBeginPeriod */
#include <stdint.h>   /* uint64_t */
#include <time.h>     /* _tzset */

struct timezone {
  int tz_minuteswest; /* minutes W of Greenwich */
  int tz_dsttime;     /* type of dst correction */
};

static int gettimeofday(struct timeval *tv, struct timezone *tz) {
  static const uint64_t epoch = 116444736000000000ULL;
  static int tzflag = 0;
  FILETIME ft;
  ULARGE_INTEGER ui;
  uint64_t tmres;

  GetSystemTimeAsFileTime(&ft);

  ui.u.LowPart = ft.dwLowDateTime;
  ui.u.HighPart = ft.dwHighDateTime;

  /* convert into microseconds */
  tmres = (ui.QuadPart - epoch) / 10;

  tv->tv_sec = (long)(tmres / 1000000);
  tv->tv_usec = (long)(tmres % 1000000);

  if (tz) {
    if (!tzflag) {
      _tzset();
      tzflag = 1;
    }

    tz->tz_minuteswest = _timezone / 60;
    tz->tz_dsttime = _daylight;
  }

  return 0;
}
#else
#include <errno.h>    /* errno */
#include <sys/time.h> /* gettimeofday */
#include <time.h>     /* nanosleep */
#endif

#include "hrtime.h"

static const unsigned short days_since_jan1[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

void hrperiod(int enable) {
#ifdef _WIN32
  if (enable)
    timeBeginPeriod(1);
  else
    timeEndPeriod(1);
#else
  ((void)enable);
#endif
}

double hrtime(long *sec, long *usec) {
  struct timeval time;

  gettimeofday(&time, NULL);

  if (sec)
    *sec = time.tv_sec;
  if (usec)
    *usec = time.tv_usec;

  return time.tv_sec + time.tv_usec / 1000000.0;
}

void hrdelay(double seconds) {
#ifndef _WIN32
  int was_error;
  struct timespec elapsed, tv;

  elapsed.tv_sec = (time_t)seconds;
  elapsed.tv_nsec = (long)((seconds - elapsed.tv_sec) * 1000000000);

  do {
    errno = 0;

    tv.tv_sec = elapsed.tv_sec;
    tv.tv_nsec = elapsed.tv_nsec;

    was_error = nanosleep(&tv, &elapsed);
  } while (was_error && (EINTR == errno));
#else
  Sleep((DWORD)(seconds * 1000.0));
#endif
}

double hrclock(void) {
#ifndef _WIN32
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  return now.tv_sec + now.tv_nsec / 1000000000.0;
#else
  static LARGE_INTEGER frequency = {0};
  LARGE_INTEGER now;

  if (0 == frequency.QuadPart)
    QueryPerformanceFrequency(&frequency);

  QueryPerformanceCounter(&now);
  return now.QuadPart / (double)frequency.QuadPart;
#endif
}

int hrtimezone(void) {
  int time_zone;
  struct tm lt, ut;
  time_t ts = time(NULL);

#ifdef _WIN32
  localtime_s(&lt, &ts);
  gmtime_s(&ut, &ts);
#else
  localtime_r(&ts, &lt);
  gmtime_r(&ts, &ut);
#endif

  time_zone = lt.tm_hour - ut.tm_hour;

  if (time_zone < -12)
    return time_zone + 24;
  if (time_zone > 12)
    return time_zone - 24;

  return time_zone;
}

int hrisleapyear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int hrdaysinmonth(int year, int month) {
  int mdays = days_since_jan1[month] - days_since_jan1[month - 1];
  return month == 2 && hrisleapyear(year) ? mdays + 1 : mdays;
}

int hryearday(int year, int month, int day) {
  int yday = days_since_jan1[month - 1] + day;
  return month > 2 && hrisleapyear(year) ? yday + 1 : yday;
}
