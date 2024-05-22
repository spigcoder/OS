#include<iostream>
#include<string>
#include<unistd.h>
using namespace std;

int main(int argc, char* argv[], char* env[]){
	//用于验证chdir系统调用
	sleep(10);
	cout << "start change dir" << endl;
	if(argc == 2){
		chdir(argv[1]);	
	}
	sleep(10);
	//用于验证环境变量
	//for(int i = 0; env[i]; ++i){
	//	cout << i << " " << env[i] << endl;
	//}
	//用于验证命令行参数
	//for(int i = 0; argv[i]; ++i){
	//	cout << i << " " << argv[i] << endl;
	//}	
	//用于验证环境变量
	//string tmp(getenv("USER"));
	//if(tmp.compare("root") == 0){
	//	cout << "you are root, you can do anything" << endl;	
	//}else{
	//	cout << "you are't root, you can't do anything" << endl;	
	//}	
	return 0;
}
