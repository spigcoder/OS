#include<iostream>
#include<sys/types.h>
#include<cstdio>
#include<cstdlib>
#include<sys/stat.h>
#include<string>
#include<unistd.h>
#include<fcntl.h>
using namespace std;
const string FILENAME = "pipe.txt";
const mode_t MODE = 0664;
