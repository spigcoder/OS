#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
int i = 0;

//thread()
// void *ThreadRoutine(void *args){
//     int num = 10000;
//     while(num--){
//         i++;
//     }
//     return nullptr;
// }

// void TestThread(){
//     pthread_t tid;
//     pthread_create(&tid, nullptr, ThreadRoutine, nullptr);
//     int num = 100000;
//     while(num--){
//         i++;
//     }
//     pthread_join(tid, nullptr);
// }

int main(){
    // TestThread();
    cout << i << endl;
    return 0;
}