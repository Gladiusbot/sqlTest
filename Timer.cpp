#include "Timer.h"

Timer::Timer() { m_start = std::chrono::high_resolution_clock::now(); }
Timer::~Timer() { Stop(); }
void Timer::Stop() {
  auto endTime = std::chrono::high_resolution_clock::now();
  auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start)
                   .time_since_epoch()
                   .count();
  auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime)
                 .time_since_epoch()
                 .count();
  auto duration = end - start;
  double ms = duration * 0.001;
  std::cout << ms << "ms\n";
}