#include <iostream>
using namespace std;

int count = 1;  //ȫ�ֱ���

int fun(){
    static int count = 10; //�ڵ�һ����j���������ʱ�򣬱���count����ʼ��Ϊ10! j�����Լ�1�� �Ժ�ÿ����j�ú����� count��ֵ����һ�κ�������֮���ֵ
    return count--; //�Ͳ��ᱻ�ٴγ�ʼ���ˣ������Լ�1�Ĳ����� ��static����ǰ��Ҫ�ﵽͬ���Ĺ��ܣ���ֻ��ʹ��ȫ�ֱ���
}

//int count = 1
