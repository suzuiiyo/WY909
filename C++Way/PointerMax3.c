#include <stdio.h>
#include <stdlib.h>

//�ص�����
void populate_array(int *array, int arraySize, int(*getNextValue)(void))
{
    int i;
    for(i=0; i<arraySize; i++){
        *(array+i) = getNextValue();
    }
}

//��ȡ���ֵ
int getNextRandomValue(void)
{
    return rand();
}

int main(void){
    int myarray[10];
    int i;
    populate_array(myarray, 10, getNextRandomValue);
    for(i=0; i<10; i++){
        printf("%d ", myarray[i]);
    }
    printf("\n");
    return 0;
}