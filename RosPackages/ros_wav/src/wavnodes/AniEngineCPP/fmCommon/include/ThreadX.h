#pragma once

#include <atomic>
#include <thread>
#include <chrono>
#include <functional>
namespace fmCommon {
class ThreadX {
 public:
  ThreadX();
  ~ThreadX();

  bool Start(std::function<void()>& worker_function,
             const size_t& sleep = 0);
  bool Stop();
  bool Wait();

 private:
  std::atomic<bool> status_{false};
  std::unique_ptr<std::thread> worker_{nullptr};
};

}  // namespace Helpers
