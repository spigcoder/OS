#include "Protocol.hpp"

void TestRequest(){
    Request rq(4312, '+', 1234);
    const string ret = rq.Serialize();
    cout << ret << endl;
    //rq.DeSerialize("12345 + 54321");
    rq.Print();
}
void TestResponse(){
    Reponse rp(1, 2);
    const string ret = rp.Serialize();
    cout << ret << endl;
    //rp.DeSerialize("1234 9");
    rp.Print();
}

//这里是测试添加报文和解除报文的操作
void TestCode(){
    string code = "1 + 2";
    int num = 5;
    Encode(code);
    cout << code;
    //解除报文
    string ret = Decode(code);
    if(ret.empty()) cout << "nihao " << endl;
    cout << ret;
}

int main(){
    TestCode();
    //TestRequest();
    //TestResponse();
    return 0;
}
