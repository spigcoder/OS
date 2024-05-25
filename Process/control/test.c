#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<errno.h>

void child(){
	printf("I'm a child, my pid is %d\n", getpid());
}

void test_fork(){
	int cnt = 3;
	while(cnt--){
		pid_t id = fork();
		if(id == 0){
			child();
			//思考一下这里如果不退出会怎么样
			//如果这里没有exit那么子进程会接着创建子进程最后会有2^cnt - 1个进程
			exit(0);	
		}	
	}
}

void test_return(){
	//test_return 是用来测试退出码的，很对时候不同的退出码有着不同的错误信息
	//使用strerror可以来查看各个错误码对应的信息
	//for(int i = 0; i < 20; ++i){
	//	printf("i: %d, return message is %s\n", i, strerror(i));
	//}
	//errno is a strategic value it is the number of last eror
	//char*tmp = (char*)malloc(1000*1000*4*1000);
	//printf(" return message is %s\n",  strerror(errno));
	//程序退出无非就是三种结果 1.正常执行然后退出， 2.错误执行然后退出
	//3.代码异常终止：异常终止的本质就是进程收到对应的信号（kill -l可以查看）
	//while(true){
	//	//printf的打印信息如果不加\n会暂存在缓冲区不会显示，进程结束之后才会结束
	//	printf("I'm a Linux Process\n");	
	//	sleep(1);
	//}
	//还有一个退出码是_exit(int status)它与exit的区别就在于_exit()是系统调用
	//exit()是库函数，exit还会执行用户自定义的清理函数关闭缓冲关闭流等
	//可以不加\n来验证会不会关闭流
	//printf("I'm a Linux Process");	
	//sleep(3);
	//_exit(11);	
}

int main(){
	test_fork();
	//test_return();
	return 0;
}
