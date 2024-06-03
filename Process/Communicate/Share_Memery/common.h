#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<cstdlib>
#include<cstdio>

class SMemory{
public:
    SMemory(size_t Size = 4096, const char* PathName = "/home/candy", int Pro_id = 2345)
    :_SIZE(Size), _PATHNAME(PathName), _Pro_Id(Pro_id)
    {}

    key_t GetKey(){
        key_t key = ftok(_PATHNAME, _Pro_Id);
        if(key == -1){
            perror("ftok: ");
            exit(1);
        }else{
            return key;
        }
    }

    int SMemoryHelper(const int flag){
        key_t key = GetKey();
        int m_id = shmget(key, _SIZE, flag);
        if(m_id == -1){
            perror("shmget: ");
            exit(1);
        }else{
            return m_id;
        }
    }

    int CreateMemory(){
        return SMemoryHelper(IPC_CREAT | IPC_EXCL | 0664);

    }

    int GetMemory(){
        return SMemoryHelper(IPC_CREAT);
    }

    ~SMemory(){
        int m_id = GetMemory();
        shmctl(m_id, 0, nullptr);
    }

    size_t size(){
        return _SIZE;
    }

private:
    size_t _SIZE;
    const char* _PATHNAME;
    int _Pro_Id;
};