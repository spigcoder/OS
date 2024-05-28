#include<stdio.h>
#include<unistd.h>
#include<string.h>

void test_buffer(){
	char* message = "I'm fwrite";
	char* mes= "I'm write";
	fprintf(stdout, "I'm fprintf");
	printf("I'm printf");
	fwrite(message, strlen(message), 1, stdout);
	write(1, mes, strlen(mes));
	//如果关闭close(1)就只有write会打，因为这里有一个语言级别的缓冲区存在
	//close(1);
	//fork()时如果是向文件中重定向，write只会写一份但是其他的会写两份，这与子进程
	//拷贝父进程的缓冲区有关
	fork();
}



int main(){

	test_buffer();
	return 0;
}
