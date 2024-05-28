#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<assert.h>

#define filename "log.txt"


void test_f_file_function(){
	//w是打开文件从头开始写，然后如果文件不存在创建，如果存在将这个文件清空	
	//FILE* fl = fopen(filename, "w");
	//这里如果不带文件路径就是从当前进程的路径下寻找->进程中有一个cwd属性
	chdir("../");
	FILE* fl = fopen(filename, "a");
	fprintf(fl, "file\n");
	fclose(fl);
}

void test_file_function(){
	//open，close，write这些都是一些系统调用fopen这些是对系统调用的封装
	//这里的第二个参数是一种比特位级别的传参，最后一个参数是创建的文件的权限
	const char* message = "Hello File\n";
	close(1);
	int fd = open(filename, O_WRONLY|O_CREAT|O_APPEND, 0666);
	ssize_t len = strlen(message);
	//这里就可以联想到以前的知识，就是我们说过在c语言中会默认打开3个流
	//stdin, stdout, stderr这三个流分别对应的文件描述符就是0，1，2所以我们创建新文件是就是从
	//3开始的，这里也可以知道文件创建的规律，就是从0开始找到一个没有的文件来创建
	ssize_t num = write(1, message, len);
	assert(num == len);
	close(fd);
}

//使用这个就可完成shell中的< 和 >> 重定向操作
void test_dup(){
	const char* message = "Hello File\n";
	int fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	ssize_t len = strlen(message);
	//将stdout重定向位fd
	dup2(fd, 1);	
	write(fd, message, len);
	write(1, message, len);
	printf("I'm printf\n");
	fprintf(stdout, "I'm fprintf\n");
}

int main(){
	//test_f_file_function();
	//test_file_function();
	test_dup();
	return 0;
}
