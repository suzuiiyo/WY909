#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand((unsigned)time(NULL));
    enum day{
        saturday,
        sunday,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday
    }workday;

    int a = rand()%7;
    enum day weekend;
    weekend = (enum day) a;  //����ת��
    //weekend = 0;   //����
    printf("weekend:%d", weekend);
}