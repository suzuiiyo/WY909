#include <iostream>
using namespace std;

//ȫ�ֱ�������
int g = 99;

//��������
int func();

int main()
{
    //�ֲ���������
    int g = 10;
    //cout << g;
    int kk = func();
    cout << kk;
    return 0;
}

//��������
int func(){
    return g;
}