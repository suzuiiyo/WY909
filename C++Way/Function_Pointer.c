#include <stdio.h>

void func1(int *a, int **b)
{
    (*a)++;
    (*b)++;//������Ȼ����������ָ����ʽ������ʵ��ָ��c�ĵ�ַ��
            //������Ϊ���ﱾ�ʻ���ֵ���ݣ�ֻ�������ֵ�ǵ�ֵַ
}

int main(){
    int a[2] = {10, 20};
    int *b   = &a[0];
    int *c   = a + 1;
    int **d  = &c;

    func1(b, d);
    printf("%p %p %p\n", *b, *c, **d);
    printf("a[0]=%d  a[1]=%d\n", a[0], a[1]);

    return 0;
}