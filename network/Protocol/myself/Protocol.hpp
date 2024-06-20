/*目的是将要传递的信息进行序列化和反序列化，并设置添加报头和去除报头的功能*/
#include <iostream>
#include <string>
using namespace std;

const string SEPARATOR = " ";
const string PROSEP = "\n";

//添加报头 结果是这样的   content_size + \n + content + \n 
void Encode(string& content){
    string masthead = to_string(content.size());
    masthead += PROSEP;
    content = masthead + content;
    content += PROSEP;
}

//将内容从报文中提取出来
string Decode(string& package){
    size_t pos = package.find(PROSEP);
    string len_str = package.substr(0, pos);
    //len是正文的长度
    size_t len = stoi(len_str);
    size_t total_len = len + sizeof(len_str) + 2;
    //这里证明内容不完整
    if(len > total_len) return "";
    //这里进行提取操作
    string ret = package.substr(pos+1, len); 
    //消除已经提取的报文
    package.erase(0, total_len);
    return ret;
}

//目的是将其转换位 "x op y"的形式
class Request{
public:
    Request(int data1, char op, int data2)
    :_x(data1), _y(data2), _op(op)
    {}
public:
    const string Serialize(){
        //将Ruquest的各个内容序列化然后返回
        string ret = "";
        ret += to_string(_x);
        ret += SEPARATOR;
        ret += _op;
        ret += SEPARATOR;
        ret += to_string(_y);
        return ret;
    }

    //"x op y"
    bool DeSerialize(const string& package){
        //将传递来的包裹打包到request当中去
        size_t first_pos = package.find(SEPARATOR); 
        if(first_pos == string::npos) 
            return false;
        size_t last_pos = package.rfind(SEPARATOR);
        if(last_pos == string::npos) 
            return false;
        if(first_pos+2 != last_pos) 
            return false;
        //现在可以提取
        _x = stoi(package.substr(0, first_pos));
        _op = package[first_pos+1];
        _y = stoi(package.substr(last_pos+1));
        return true;
    }

    void Print(){
        cout << _x << " " << _op << " " << _y << endl;
    }

private:
    int _x;
    int _y;
    char _op;
};


//处理相应，这也要进行序列化和反序列化
class Reponse{
public:
    Reponse(int result, int code)
    :_result(result), _code(code)
    {}
public:
    const string Serialize(){
        string ret = "";
        ret += to_string(_result);
        ret += SEPARATOR;
        ret += to_string(_code);
        return ret;
    }

    bool DeSerialize(const string& package){
        size_t pos = package.find(SEPARATOR);
        if(pos == string::npos)
            return false;
        _result = stoi(package.substr(0, pos));
        _code = stoi(package.substr(pos+1));
        return true;
    }

    void Print() {
        cout << "code: " << _code << "result: " << _result << endl;
    }

private:
    //_result用来表示结果，_code用来表示结果是否正确
    int _result;
    int _code;
};





































