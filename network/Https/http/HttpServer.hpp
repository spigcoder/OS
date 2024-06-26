#include "Socket.hpp"
#include <fstream>
#include <pthread.h>
#include <vector>
#include <sstream>
using namespace std;

//sep时每一行http协议的分割方式
const string HOME = "./root";
const string sep = "\r\n";
const int BUFFSIZE = 10240;

class Server;

class Request{
public:
    void DeSerialize(string comment){
        //将http相应中的所有的内容都加载到分开加载到对应的内容当中取
        while(true){
            size_t pos = comment.find(sep);
            if(pos == string::npos) break;
            string tmp = comment.substr(0, pos);
            //这里证明遇到了空行，那么下一行就是request 的正文
            if(tmp.empty()) break;
            _header.push_back(tmp);
            comment.erase(0, pos+sep.size());
        }
        _text = comment;
    }

    //将第一行中的Methond url version都加载到对应的string字符串当中，并且通过url找到路径名称
    void Parse(){
        stringstream ss(_header[0]);
        ss >> _methond >> _url >> _http_version;
        //根据url来进行路径分配
        _file_path = HOME;
        if(_url == "/" || _url == "index.html"){
            _file_path += "/index.html";
        }else{
            _file_path += _url;
        }
    }

    void PrintDebug(){
        for(auto line : _header){
            cout << "------------------------" << endl;
            cout << line << endl;
        }
        cout << "Methond: " << _methond << endl;
        cout << "url: " << _url << endl;
        cout << "http_version: " << _http_version << endl;
        cout << "file_path: " << _file_path;
    }

public:
    vector<string> _header;
    string _methond;
    string _url;
    string _http_version;
    string _text;
    string _file_path;
    //这里可以再有一个后缀，根据不同的后缀可以使用不同的解码方式
};

struct Thread_Data{
    Thread_Data(Server* th, int sock_fd)
    :_server(th), _sock_fd(sock_fd)
    {}

public:
    Server* _server;
    int _sock_fd;
};


class Server{
public:
    Server(const uint16_t port = PORT):_port(PORT){

    }

    string ReadHtmlContent(const string& file_path){
        cout << "file_path" << file_path << endl;
        ifstream in(file_path, ios::binary);
        //这里是如果没有打开就返回空
        if(!in.is_open()) return "";
        //计算文件的大小

        //将光标置于最后的位置
        in.seekg(0, ios::basic_ios::end);
        //计算当前光标的所在的位置，如果这时光标处于最后的位置的话就是整个文件的大小
        size_t len = in.tellg();
        //将光标置于开始处
        in.seekg(0, ios::basic_ios::beg);

        string content;
        content.resize(len);
        in.read((char*)content.c_str(), content.size());

        in.close();
        return content;
    }

    void Finish(int sock_fd){
        //这里就是对port进行读取并且处理数据的地方
        char buff[BUFFSIZE];
        //进行读取操作
        ssize_t n = read(sock_fd, buff, sizeof(buff) - 1);
        if(n > 0){
            buff[n] = 0;
            //对读取到的数据进行反序列化操作让其成为一个request
            cout << buff << endl;
            Request req;
            req.DeSerialize(buff); 
            req.Parse();
            req.PrintDebug();
            //现在req中就是存放的相应的内容了
            string content = ReadHtmlContent(req._file_path);
            //如果ok是true就证明访问的页面时存在的正确的，否则就是false
            bool ok = true;
            if(content.empty()){
                //走到这里证明要访问的页面不存在所以打开404页面
                ok = false;
                string file_path = HOME;
                file_path += "/error.html";
                content = ReadHtmlContent(file_path);
            }
            string header; 
            string response_line; 
            if(ok){
                //这里证明网页存在可以访问
                response_line = "HTTP/1.0 200 OK\r\n";
            }else{
                response_line = "HTTP/1.0 404 Not Found\r\n";
            }
            //相应包头的内容
            string response_header = "Content-Length: ";
            response_header += std::to_string(content.size()); // Content-Length: 11
            response_header += "\r\n";

            //response_header += "Location: https://www.qq.com\r\n";
            //空行
            std::string blank_line = "\r\n"; // \n

            std::string response = response_line;
            response += response_header;
            response += blank_line;
            response += content;

            write(sock_fd, response.c_str(), response.size());
        }else{
            cout << "can't get a finish" << endl;
        }
        close(sock_fd);
    }

    static void* Routine(void* args){
        //线程这里要进行线程的分离
        pthread_detach(pthread_self());
        Thread_Data* data = static_cast<Thread_Data*>(args);
        data->_server->Finish(data->_sock_fd);
        delete data;
        return nullptr;
    }

    void Start(){
        //首先进行接听操作        
        cout << "get start" << endl;
        int n = _listen_socket.Bind();
        if(n) cout << "bind sucess" << endl;
        n = _listen_socket.Listen();
        if(n) cout << "listen sucess" << endl;
        uint16_t client_port;
        string client_ip;
        while(true){
            int sock_fd = _listen_socket.Accept(client_ip, client_port);
            if(sock_fd < 0){
                perror("accept fail: ");
                continue;
            }
            cout << "get accept from" << client_ip << endl;
            //读取到了请求的信息，可以创建新线程来进行网页处理操作
            pthread_t pid;
            Thread_Data* data = new Thread_Data(this, sock_fd);
            pthread_create(&pid, nullptr, Routine, data);
        }
    }

private:
    Socket _listen_socket;
    uint16_t _port;
};





