#include "ThreadX.h"

#include <iostream>
#include <stdexcept>

namespace fmCommon
{

ThreadX::ThreadX() {}
ThreadX::~ThreadX() {
  if (Stop()) Wait();
}

bool ThreadX::Start(std::function<void()>& worker_function,
                                const size_t& sleep) {

  if (status_ == true || worker_ != nullptr) {
    return false;  // Already occupied
  }
  status_ = true;

  worker_.reset(new std::thread([&, worker_function, sleep]() {
    while (status_) {
      worker_function();
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }
  }));
  
  return false;
}

bool ThreadX::Stop() {
  if (status_ == false) return false;
  status_ = false;
  return true;
}

bool ThreadX::Wait() {
  if (worker_ != nullptr) {
    try{
      if(worker_->joinable())
      worker_->join();
   
    status_ = false;
    worker_.reset(nullptr);
    }catch(std::exception &e){
      std::cout<<"Exception: "<<e.what()<<std::endl;
    }

    return true;
  }
  return false;
}

}