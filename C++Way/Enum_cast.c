#include<stdio.h>

enum DAY
{
    MON=1, TUE, WED, THU, FRI, SAT, SUN
}weekend;

int main(){
    weekend=MON;
    printf("day is %d\n", weekend);
    //����ö��Ԫ��
    while(weekend <= SUN){
        printf("ö��Ԫ��: %d \n", weekend);   //����ǿ��ת��
        weekend = (enum DAY)(weekend + 1);
    }
}