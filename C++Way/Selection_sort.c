#include<stdio.h>

void swap(int *a, int *b)  //������������
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int arr[], int len)
{
    int i, j;

    for(i=0; i<len; i++){
        int min = i;
        for(j=i+1; j<len; j++)          //�߷�δ�����Ԫ��
            if(arr[j] < arr[min])           //�ҵ�Ŀǰ��Сֵ
                min = j;                   //��¼��Сֵ
            swap(&arr[min], &arr[i]);      //������
    }
}

int main(){
    int arr[] = {2312, 34, 451, 54, 1344, 767, 232, 767, 7213, 532};
    int len = (int)(sizeof(arr)/sizeof(*arr));
    selection_sort(arr, len);
    for(int i=0; i<len; i++){
        printf("arr[%d}: %d\n", i, arr[i]);
    }
}