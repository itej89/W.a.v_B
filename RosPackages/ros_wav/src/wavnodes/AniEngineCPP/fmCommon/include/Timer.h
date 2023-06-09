#pragma once

//#include <android/log.h>

#include <iostream>
#include <functional>
#include <thread>
#include <atomic>
#include <chrono>


 // #define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "FM_KINETICS", __VA_ARGS__);

namespace fmCommon
{
    
class Timer {
    bool clear = false;

    public:
        
    // template<typename Function>
    // void setTimeout(Function function, int delay);

    // template<typename Function>
    // void setInterval(Function function, int interval);
        template<typename Function>
    void setTimeout(Function function, int delay) {
        this->clear = false;
        std::thread t([=]() {
            printf("Timer Start");
            int counter = 0;
            while(this->clear == false)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                counter ++;
                if(counter >= delay)
                {
                    printf("Timer Timeout");
                    function();
                    this->clear = true;
                }
            }
        });
        t.detach();
    }


    void setTimeoutTimer(std::function<void()>& worker_function, int delay) {
        this->clear = false;
        std::thread t([=]() {
            printf("Timer Start\n");
            int counter = 0;
            while(this->clear == false)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                counter ++;
                if(counter >= delay)
                {
                    printf("Timer Timeout\n");
                    worker_function();
                    this->clear = true;
                }
            }
        });
        t.detach();
    }

    void setIntervalTimer(std::function<void()>& worker_function, int interval) {
        this->clear = false;
        std::thread t([=]() {
            while(true) {
                if(this->clear) return;
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                if(this->clear) return;
                worker_function();
            }
        });
        t.detach();
    }

    template<typename Function>
    void setInterval(Function function, int interval) {
        this->clear = false;
        std::thread t([=]() {
            while(true) {
                if(this->clear) return;
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                if(this->clear) return;
                function();
            }
        });
        t.detach();
    }
            
    void stop() {
        // printf("Timer Stop");
        this->clear = true;
    }

};


  



}