#include <iostream>
#include <cstring>
using namespace std;

constexpr size_t NUM = 101;
constexpr size_t COUNT = 4;
constexpr char STYLE = '=';
constexpr char POINT = '.';
constexpr char SPACE = ' ';

//根据总长度还有当前的进度进行进度条的打印
void ProgressBar(double total, double current){
    double percentage = current / total * 100;

    char progress_bar[NUM];
    char buffer[COUNT+1];
    buffer[COUNT] = '\0';
    memset(progress_bar, '\0', sizeof(progress_bar));
    for(int i = 0; i < (int)percentage; ++i){
        progress_bar[i] = STYLE;
    }

    static size_t count = 0;
    count++, count %= COUNT+1;
    for(int i = 0; i < count; ++i){
        if(count == COUNT) buffer[i] = SPACE;
        else buffer[i] = POINT;
    }
    //打印
    printf("[%-100s][%.2f%%]%s\r", progress_bar, percentage, buffer);
    fflush(stdout);
}
