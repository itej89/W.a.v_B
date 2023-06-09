#include <unistd.h>
#include <iostream>
#include <limits.h>
#include <vector>
#include <string>
#include <functional>

#include "TimerTest.h"



TimerTest::TimerTest()
{

}

void TimerTest::setTimeoutInterval()
{
    Timer Timeout;
      std::function<void(void)>  looper = std::bind(&TimerTest::TimeoutInterval ,this);
    Timeout.setIntervalTimer(looper, 1000);
}

void TimerTest::TimeoutInterval()
{
    printf("Timer Ticked!!!");
}


void TimerTest::setTimeout()
{
    Timer Timeout;
      std::function<void(void)>  looper = std::bind(&TimerTest::Timeout ,this);
    Timeout.setTimeoutTimer(looper, 1000);
}

void TimerTest::Timeout()
{
    printf("Timer Done!!!");
}


TEST_F(TimerTest, TimerTest) {
    setTimeout();
    setTimeoutInterval();
}