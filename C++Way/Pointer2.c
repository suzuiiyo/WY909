#include <stdio.h>

int main(){
    int var = 20;   /* 实际变量的声明*/
    int *ip;        /* 指针变量的声明 */
    ip = &var;    /*再指针变量中存储var的地址 */

    printf("Address of var variable: %p\n", &var);

    /*在指针变量中存储的地址 */
    printf("Address stored in ip variable: %p\n", ip);

    /* 使用指针访问值 */
    printf("Value of *ip variable: %d\n", *ip);

    return 0;
}