#include<iostream>
#include<unistd.h>
using namespace std;

int main(){
	//用于验证运行态，如果在循环中打印东西可以验证阻塞态
//	while(1);
	//验证僵尸进程 -> 就是说子进程已经结束了，但是父进程还没有来进行资源的回收
	//pid_t id = fork();
	//if(id == 0){
	//	int cnt = 4;
	//	while(cnt--){
	//		cout << "I'm a child my pid is " << getpid() << "my ppid is " << getppid() << endl;
	//		sleep(1);
	//	}
	//}else{
	//	while(true){
	//		cout << "I'm a father my pid is " << getpid() << "my ppid is " << getppid() << endl;
	//		sleep(1);
	//	}	
	//}
	//这个用来验证孤儿进程，就是父进程被杀掉了然后子进程由1号进程领养
	pid_t id = fork();
	if(id == 0){
		while(true){
			//这里在使用c语言的打印时出了点问题，所以最好不要混着用
			cout << "I'm a child my pid is " << getpid() << "my ppid is " << getppid() << endl;
			sleep(1);
		}
	}else{
		int cnt = 4;
		while(cnt--){
			cout << "I'm a father my pid is " << getpid() << "my ppid is " << getppid() << endl;
			sleep(1);
		}	
	}
	return 0;
}
