#include <stdio.h>

int main(){
    char c[10];
    char *ptr;
    ptr = c;
    printf("ptr �ĵ�ַ�� %p\n", ptr);

    int var = 20;   /* ʵ�ʱ��������� ��ʱ��var��������Ǵ���ĳ����ַ�ģ� ��ַ��Ӧĳ���ڴ浥Ԫ���õ�Ԫ�д洢������20 */
    int *ip;   /*ָ����������� ������һ��ָ�뼴һ���ڴ浥Ԫ��ָ����� */
    ip = &var;  /*��ָ������д洢var�ĵ�ַ ���ǽ�j��ֵַ��ֵ��ָ��������� */

    /*��ָ������д洢�ĵ�ַ  ����&����ֱ�������var���洢�����ݵ��ڴ浥Ԫ�ĵ�ַ*/
    printf("Address of var variable: %p\n", &var);

    /*��ָ������д洢�ĵ�ַ ip������������ֵ���ĵ�ַ��ֵ  ����������ǵ�ֵַ */
    printf("Address stored in ip variable: %p\n", ip);

    /*ʹ��ָ�����ֵ *ip������Ƕ��嵽����ڴ浥Ԫ֮���ڴ浥Ԫ�����洢�����ݵ�ֵҲ��j��20������var��20�����ֵ  */
    printf("Value of *ip variable: %d\n", *ip);

    return 0;
}