#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/wait.h>

void test_exel(){
	//execl("/usr/bin/ls", "ls", "-l", "-a", NULL);
	execlp("ls", "ls", "-l", "-a", NULL);
	//程序替换就是将代码段和代码段进行替换，然后执行替换之后的进程而不再执行替换之前的进程
	printf("你好\n");
}

void test_execv(){
	//这里在使用vector传递参数时不能将NULL给忘记了
	char *const argv[] = {"ls", "-l", "-a", NULL};
	//execv("/usr/bin/ls", argv);
	execvp("ls", argv);
}

void test_exe(){
	execl("./test", "test", "-a", NULL);
}

int main(){
	//test_exel();
	//test_execv();
	//这个是调用自己写的函数
	test_exe();
	return 0;
}


















