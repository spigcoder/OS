#include"common.hpp"
const int SZ = 1024;

void Read(){
    while(true){
        int fd = open(FILENAME.c_str(), O_RDONLY);
        char mes[SZ] = {0};
        int x = read(fd, mes, sizeof(mes));
        if(x > 0){
            mes[x] = 0;//添加\0
            cout << "Client say# " << mes << endl;
        }
    }
}

int main(){
    Read();
    return 0;
}