#include<stdio.h>

int A=10;
int B=20;
char buy;
int sum, number;

int main(){
    printf("�����Ǳ�����̼��۸�: \n A ��Ʒÿ��ʮԪ��\n B ��Ʒÿ����ʮԪ; \n\n");
    printf("������������Ҫ�������Ʒ(A �� B):");
    scanf("%c", &buy);
    printf("���������蹺�������: ");
    scanf("%d", &number);
    sum=buy== 'A'?A*number:B*number;
    printf("\n������Ҫ��%d��%c��Ʒ�ܹ�%dԪ�� \n", number, buy, sum);

    return 0;
}