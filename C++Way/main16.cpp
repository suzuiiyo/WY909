#include <iostream>

void func(void);

static int count = 10;  /* ȫ�ֱ��� */

int main(){
    while(count--){
        func();
    }
    return 0;
}

//��������
void func(void){
    static int i =5; //�ֲ�j��̬����
    i++;
    std::cout << "���� i Ϊ" << i;
    std::cout << ", ����countΪ "  << count << std::endl;

}