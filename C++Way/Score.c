#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int score[10];
    int len = sizeof(score)/sizeof(int);
    int count=0;   //����������ͳ���ж����˴ﵽƽ����
    int i;
    srand((unsigned)time(NULL));

    //��������
    for(i=0; i<len; i++){
        score[i] = rand()%68 + 32;
        printf("score[%d]=%d\t", i, score[i]);
    }

    //�����ݽ������
    int sum =0;
    for(i=0; i<len; i++){
        sum += score[i];
    }

    //��ƽ����
    double arg=sum/len;
    //�ж��ж����˴ﵽƽ����;
    for(i=0; i<len; i++){
        if(score[i]>arg){
            count++;
        }
    }

    //���ƽ���ֺ�����
    printf("\n�ܷ�Ϊ: %d\nƽ����Ϊ: %0.2f\n����ƽ���ֵ�����: %d��\n", sum, arg, count);
}

