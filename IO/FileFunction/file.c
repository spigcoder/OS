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
