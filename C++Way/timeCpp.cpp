#include <iostream>
#include <ctime>

using namespace std;

int main(){
    //���ڵ�xϵͳ������ / ʱ��
    time_t now = time(0);

    //��nowת��Ϊ�ַ�����ʽ
    char* dt = ctime(&now);

    cout << "�������ں�ʱ��: " << dt << endl;

    //��nowת��Ϊtm�ṹ
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    cout << "UTC ���ں�ʱ��: " << dt << endl;
}