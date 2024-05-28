#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/wait.h>

const int NUM = 5;

void child(){
	int cnt = 1;
	while(cnt--){
		printf("I'm a child my pid is %d, my ppid is %d, cnt : %d\n", getpid(), getppid(), cnt);
		sleep(1);
	}
}

void father(pid_t pid){
	int cnt = 1;
	while(cnt--){
		printf("I'm a father my pid is %d, my ppid is %d, cnt : %d\n", getpid(), getppid(), cnt);
		sleep(1);
	}
}

void test_for_OneProcess_wait(){
	pid_t id = fork();
	if(id == 0){
		child();
		exit(0);	
	}
	else if(id > 0){
		father(id);
	}
	//这里要进行进程的回收操作，使用wait或者waitpid
	int status = 0;
	//status是输出型参数，分为很多部分0~7位表示充值信号，8~15位表示退出状态
	pid_t ret = wait(&status);
	if(ret < 0){
		perror("wait fail\n");	
	}else{
		printf("wait success, exit code: %d, exit singal: %d\n",(status>>8)&0xFF , status&0x7F);	
	}
	sleep(2);
}

void test_for_NumsProcess_wait(){
	for(int i = 0; i < NUM; ++i){
		pid_t id = fork();	
		if(id == 0){
			child();
			exit(i);	
		}else{
			father(id);	
		}
	}
	int status = 0;
	//如果只是使用wait的化wait只有一个参数status，只要循环和NUM相同的次数即可
	for(int i = 0; i < NUM; ++i){
		pid_t ret = wait(&status);	
		if(ret < 0){
			perror("wait fail\n");	
		}else{
			printf("wait success, exit code: %d, exit singal: %d\n",(status>>8)&0xFF , status&0x7F);	
			
		}
	}
}

void test_for_OneProcess_waitpid(){
	pid_t id = fork();
	if(id == 0){
		child();
		exit(0);	
	}
	else if(id > 0){
		father(id);
	}
	//这里要进行进程的回收操作，使用wait或者waitpid
	int status = 0;
	//status是输出型参数，分为很多部分0~7位表示充值信号，8~15位表示退出状态
//wait_pid(pid_t pid, int* status, int options) pid如果是-1就是等待任意一个子进程与id一致，option是
//一种等待的状态，可以是阻塞状态(默认option = 0)或者非阻塞巡回等待，就是直接返回子进程的状态，如果子进程
//还没有结束就返回0，如果子进程正常结束就返回子进程的id
	while(true){
		pid_t ret = waitpid(id, &status, WNOHANG);
		if(ret < 0){
			perror("wait fail\n");	
		}else if(ret > 0){
			printf("wait success, exit code: %d, exit singal: %d\n",(status>>8)&0xFF , status&0x7F);	
			break;
		}else{
			//非阻塞巡回
			printf("我还在等待\n");	
		}
	}
}

void test_for_NumsProcess_waitpid(){
	for(int i = 0; i < NUM; ++i){
		pid_t id = fork();	
		if(id == 0){
			child();
			exit(i);	
		}else{
			father(id);	
		}
	}
	int status = 0;
	for(int i = 0; i < NUM; ++i){
		pid_t ret = waitpid(-1, &status, 0);	
		if(ret < 0){
			perror("wait fail\n");	
		}else{
			printf("wait success, exit code: %d, exit singal: %d\n",(status>>8)&0xFF , status&0x7F);	
			
		}
	}
}

int main(){
	//test_for_OneProcess_wait();
	//test_for_NumsProcess_wait();
	//test_for_NumsProcess_waitpid();
	test_for_OneProcess_waitpid();
	return 0;
}


















