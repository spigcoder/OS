#include<iostream>
#include<string.h>
using namespace std;

int main(int argc, const char* argv[]){
	for(int i = 0; argv[i]; ++i){
		if(!strcmp(argv[i], "-a")) cout << "aaaa" << endl;
		if(!strcmp(argv[i], "-b")) cout << "bbbb" << endl;
	}
	cout << "Hello cpp " << endl;
	return 0;
}
