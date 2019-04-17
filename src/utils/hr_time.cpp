#include "hr_time.h"

#include <iostream>

#ifdef __linux__
#include <sys/time.h>
#include <stdio.h>

// call the constructor with the member init list
CStopWatch::CStopWatch(): cur_time_(0)
{
  startTimer();
}
//=========================================================================================


// Dtor
CStopWatch::~CStopWatch() { }
//=========================================================================================


void CStopWatch::startTimer()
{
  struct timeval time;
  if(gettimeofday( &time, 0 )) return;
  cur_time_ = 1000000 * time.tv_sec + time.tv_usec; // microsec
}
//=========================================================================================

// Get the time in msec
double CStopWatch::getElapsedTime_msec()
{
  struct timeval time;
  if(gettimeofday( &time, 0 )) return -1;

  long cur_time = 1000000 * time.tv_sec + time.tv_usec; // microsec
  double sec = (cur_time - cur_time_) / 1000000.0;
  if(sec < 0) sec += 86400;
  cur_time_ = cur_time;

  // return ms
  return sec / 1000.0;
}
//=========================================================================================


// Get the time in sec
double CStopWatch::getElapsedTime_sec()
{
  struct timeval time;
  if(gettimeofday( &time, 0 )) return -1;

  long cur_time = 1000000 * time.tv_sec + time.tv_usec; // microsec
  double sec = (cur_time - cur_time_) / 1000000.0;
  if(sec < 0) sec += 86400;
  cur_time_ = cur_time;

  // return sec
  return sec;
}
//=========================================================================================




#elif _WIN32 || _WIN64
#include <windows.h>

struct PrivateCStopWatch
{
  double  PCFreq;
  __int64 CounterStart;
};
//=========================================================================================


// Default constructor
CStopWatch::CStopWatch()
{
  privateCStopWatch = new PrivateCStopWatch;
  (*privateCStopWatch).PCFreq = 0.0;
  (*privateCStopWatch).CounterStart = 0;
}
//=========================================================================================


// Default destructor
CStopWatch::~CStopWatch()
{
  delete privateCStopWatch;
  privateCStopWatch= nullptr;
}
//=========================================================================================


// Starts the timing
void CStopWatch::startTimer()
{
  LARGE_INTEGER li;
  if(!QueryPerformanceFrequency(&li))
  {
    std::cout << "QueryPerformanceFrequency failed!\n";
  }
  (*privateCStopWatch).PCFreq = double(li.QuadPart);

  QueryPerformanceCounter(&li);
  (*privateCStopWatch).CounterStart = li.QuadPart;
}
//=========================================================================================


// Gets the timing counter in ms.
double CStopWatch::getElapsedTime_msec()
{
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  return (double(li.QuadPart-(*privateCStopWatch).CounterStart)/(*privateCStopWatch).PCFreq) * 1000;
}
//=========================================================================================


// Gets the timing counter in sec.
double CStopWatch::getElapsedTime_sec()
{
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  return double(li.QuadPart-(*privateCStopWatch).CounterStart)/(*privateCStopWatch).PCFreq;
}
//=========================================================================================


#endif
