#include<stdio.h>

/*int max(int a, int b){
    if(a >= b){
        return a;
    }else
    {
        return b;
    }
}

int main(){
    int a; int b; int c;
    printf("��ֱ�����a, b, c��ֵ: ");
    scanf("%d%d%d", &a, &b, &c);

    int max1 = max(a, b);
    int max2 = max(a, c);
    int max3 = max(max1, max2);

    printf("������������ֵ��: %d", max3);
}*/

float max(float a, float b, float c){
    return a>=b?(a>=c?a:c):(b>=c?b:c);
}

int main(){
    int a; int b; int c;
    printf("��ֱ�����a, b, c��ֵ: ");
    scanf("%d%d%d", &a, &b, &c);

    int max_value = max(a, b, c);
    printf("%d", max_value);
}


