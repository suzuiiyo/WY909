#include<stdio.h>
#include "max.h"
#include "source.h"

int main(void){
    int num1;
    int num2;
    int result;
    printf("������num1��ֵ: ");
    scanf("%d", &num1);
    printf("������num2��ֵ: ");
    scanf("%d", &num2);

    result = max(num1, num2);
    printf("result��ֵΪ: %d\n", result);

    int sum = add(num1, num2);

    int diff = sub(num1, num2);
    printf("num1��num2�ĺ�Ϊ: %d\n", sum);
    printf("num1��num2�Ĳ�Ϊ: %d\n", diff);
}