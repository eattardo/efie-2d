// 1 micro-second accuracy wall timer.

#ifndef __HR_TIME_H__
#define __HR_TIME_H__

#ifdef __linux__

class CStopWatch
{

private:
  long cur_time_;

public:

  CStopWatch();

  ~CStopWatch();

  void startTimer();

  // Get the elapsed time in sec
  double getElapsedTime_sec();

  // Get the elapsed time in msec
  double getElapsedTime_msec();

};
//=========================================================================================


#elif _WIN32 || _WIN64

struct PrivateCStopWatch;

class CStopWatch
{
private:
  PrivateCStopWatch *privateCStopWatch;

public:

  CStopWatch();

  ~CStopWatch();

  void startTimer();

  // Get the elapsed time in sec
  double getElapsedTime_sec();

  // Get the elapsed time in msec
  double getElapsedTime_msec();
}; // CStopWatch class
//=========================================================================================

#endif


#endif /* __HR_TIME_H__ */