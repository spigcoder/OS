#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<assert.h>
#include<stdbool.h>
#include<errno.h>
#include<string.h>

#define LABEL "$"
#define PATH_SIZE 50
#define ARGUMENT_SIZE 10
#define COMMANDSIZE 50 
#define delim " "

char path[PATH_SIZE];  
char CommandLine[COMMANDSIZE];
char* argv[ARGUMENT_SIZE];
size_t argc = 0;
size_t LastCode = 0;

char* GetUser(){
	return getenv("USER");	
}

char* GetPath(){
	return getcwd(path, PATH_SIZE); 
}

void interactive(){
	//1.打印基本信息
	printf("%s:%s "LABEL, GetUser(), GetPath());
	//接收信息	
	fgets(CommandLine, COMMANDSIZE, stdin);
	//这里在提取时会将\n也提取了，可以手动将其释放
	//strlen是会算上\n的
	CommandLine[strlen(CommandLine) - 1] = '\0';
}

void splice(){
	argc = 0;
	argv[argc++] = strtok(CommandLine, delim);
	//strtok在第二次使用时一定要调用NULL
	while((argv[argc++] = strtok(NULL, delim)));
	argc--;
}

void CommonCommandExecute(){
	//一般的指令都是由父进程创建子进程，然后有子进程来执行的
	pid_t id = fork();
	if(id == 0){
		//child
		execvp(argv[0], argv);	
		LastCode = errno;
		exit(errno);
	}else{
		int status = 0;
		waitpid(id, &status, 0);	
		LastCode = WEXITSTATUS(status);
	}
}

int SpeCommandExecute(){
	//因为使用exec系列的代码之后就无法再执行后续的代码，所以要用一些系统调用来完成这些工作
	if(argc == 2 && !strcmp(argv[0], "cd")){
		printf("%s", argv[0]);
		chdir(argv[1]);
		return 0;	
	}
	//这就表示他不是特殊指令
	return 1;
}

int main(){
	int quit = 1;
	while(quit){
		//交互
		interactive();
		//将参数划分开
		splice();
		//有一些指令例如cd还有echo这样的指令不使用子进程来执行而是要自己执行
		int lg = SpeCommandExecute();
		//执行一般指令
		CommonCommandExecute();
	}
	return 0;
}




