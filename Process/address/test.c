#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include <sys/types.h>

int init_val1;
int init_val2 = 100;

void test_address(){
	printf("code address is %p\n", test_address);	
	char* tmp = "hello spigcoder";
	printf("only read string address is %p\n", tmp);
	static int x = 1;
	printf("static local val address is %p\n", &init_val2);
	printf("init val address is %p\n", &init_val2);
	printf("uninit val address is %p\n", &init_val1);
	char* mac = (char*)malloc(100);
	printf("malloc address is %p\n", mac);
	printf("stack address is %p\n", &mac);
	
}

void test_virtual_address(){
	int count = 100;
	pid_t id = fork();
	if(id == 0){
		int cnt = 4;
		while(true){
			printf("I'm child my pid is %d, my ppid is %d, count is %d, cout address is %p\n", getpid(), getppid(), count, &count);	
			sleep(1);
			if(cnt) cnt--;
			else{
				count = 200;
				printf("count has be changed\n");	
				cnt--;
			}
		}	
	}
	else{
		while(true){
			printf("I'm father my pid is %d, my ppid is %d, count is %d, cout address is %p\n", getpid(), getppid(), count, &count);	
			sleep(1);
		}	
	}
}

void test_only_read_string(){
	//因为tmp指向的是字符串常量区的地址，而这个地址是只读的所以编译时不会报错，但是运行时会出现段错误
	char* tmp = "Hello spigcoder";
	*tmp = 'H';
}

int main(){
	//验证各个空间的地址的关系
	//test_address();
	//验证虚拟地址的存在
	//test_virtual_address();
	//验证字符串常量区拥有只读属性
	//test_only_read_string();	
	return 0;
}
