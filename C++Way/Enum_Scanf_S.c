#include<stdio.h>
#include<stdlib.h>

int main(){
    enum color{red = 1, green, blue};

    enum color favorite_color;

    //�û�����������ѡ����ɫ
    printf("please enter the color you like:(1. red, 2. green, 3. blue): \n");

    scanf_s("%u", &favorite_color);

    //������
    switch(favorite_color){
        case red:
            printf("You like red!");
            break;
        case green:
            printf("You like green!");
            break;
        case blue:
            printf("You like blue!");
            break;
        default:
            printf("No color you like!");
    }

    return 0;
}