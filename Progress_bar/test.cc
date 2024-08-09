#include <thread>
#include <chrono>
#include <functional>
#include "Progress_bar.hpp"

constexpr size_t SPEED = 101;
constexpr double TOTAL = 2048;

void Download(function<void(double,double)> prog_f){
    double cur = 0;
    while(cur < TOTAL){
        cur += 0.1*SPEED;
        if(cur >= TOTAL) cur = TOTAL;
        prog_f(TOTAL, cur);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
}

int main(){
    Download(ProgressBar);
    return 0;
}