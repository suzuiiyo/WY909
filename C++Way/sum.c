#include <stdio.h>

int sum(int n);

int main(){
    int n;
    printf("������n��ֵ: ");
    scanf("%d", &n);
    long long a = sum(n);
    printf("%lld", a);
    return 0;
}

int sum(int n){
    //��ͺ���ʵ��
    //���nΪ1��������ͣ�ֱ�ӷ���1
    if(n==1)
        return n;
    else
    {
        /* code */
        return n+sum(n-1);
    }
}