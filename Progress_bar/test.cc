#include <ctime>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <functional>
#include "Progress_bar.hpp"

constexpr size_t SPEED = 500;
constexpr double TOTAL = 2048;
constexpr double base = 0.1;


void Download(function<void(double,double)> prog_f){
    double cur = 0;
    while(cur < TOTAL){
        cur += base * ((rand()) % SPEED+1);
        if(cur >= TOTAL) cur = TOTAL;
        prog_f(TOTAL, cur);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
}

int main(){
    srand(time(nullptr));
    Download(ProgressBar);
    return 0;
}