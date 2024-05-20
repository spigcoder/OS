#include<iostream>
#include<unistd.h>
using namespace std;

int main(){
	while(1){
		cout << "Hello I'm a Process" << endl;
		sleep(1);
	}
	return 0;
}
