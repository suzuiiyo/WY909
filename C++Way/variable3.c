#include <stdio.h>

/* ȫ�ֱ������� */
int a = 20;

int main(){
    /* �ں�����j�ֲ��������� */
    int a = 10;
    int b =20;
    int c = 0;
    int sum(int, int);

    printf("value of a in main() = %d\n", a);
    c = sum(a, b);
    printf("value of c in main() = %d\n", c);

    return 0;
}

int sum(int a, int b){
    printf("value of a in sum() = %d\n", a);
    printf("value of a in sum() = %d\n", b);

    return a + b;
}