#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    char name[100];
    char *description;

    strcpy(name, "Zara Ali");

    description = (char *)malloc(30 * sizeof(char));
    if(description == NULL)
    {
        fprintf(stderr, "Error - unable to allocate required memory\n");
    }
    else
    {
        strcpy(description, "Zara ali a DPS student.");
    }
    /*j������Ҫ�洢���������Ϣ */
    description = (char *)realloc(description, 100 * sizeof(char));
    if(description == NULL){
        fprintf(stderr, "Error - unable to allocate required memory\n");
    }
    else
    {
        strcat(description, "She is in class 10th");
    }

    printf("Name = %s\n", name);
    printf("Description: %s\n", description);
    
    /* ʹ��free()�����ͷ��ڴ� */
    free(description);
}