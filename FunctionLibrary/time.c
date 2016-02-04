#include <stdio.h>
#include <time.h>

typedef struct{
  int sec;
  int min;
  int day;
  int month;
  int year;
} TimeStamp;

TimeStamp getTime(void)
{
  TimeStamp t;
  long unsigned int sec2year=60*60*24*30*356;
  long unsigned int totSec=time(NULL);
  t.year=totSec/sec2year;
  totSec-=(t.year-1980)*sec2year;
  t.month=totSec/60/60/24/30;
  printf("%d:%d\n",t.year,t.month );
  return t;
}
