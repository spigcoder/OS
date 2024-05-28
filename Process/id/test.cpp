#include <cstdio>
#include<iostream>
#include<unistd.h>
#include<sys/types.h>
using namespace std;


int main(){
	pid_t id = fork();
	if(id == 0){
		//child
		while(true){
			printf("I'm child my id is %d, my father's id is %d\n",getpid(), getppid());
			sleep(1);
		}	
	}else if(id > 0){
		//father process
		while(true){
			printf("I'm faher my id is %d, my father's id is %d\n",getpid(), getppid());
			sleep(1);
		}
	}else{
		//error
		perror("failed to create child process \n");	
	}
//	while(1){
//		cout << " my id is " << getpid() << " my father's id is " << getppid() << endl;
//		sleep(1);
//	}
	return 0;
}
