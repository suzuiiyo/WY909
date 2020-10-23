#include<stdio.h>
#include<string.h>

char * s_gets(char *st, int n);

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100     //�鼮���������

struct book{    //���� book ģ��
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};

int main(void){
    struct book library[MAXBKS];   // book j�ṹ��������
    int count = 0;
    int index;
    printf("����������:    \n");
    printf("����[enter]�������� \n");
    while(count < MAXBKS && s_gets(library[count].title, MAXTITL) !=NULL && library[count].title[0] != '\0')
    {
        printf("���������ߣ�\n");
        s_gets(library[count].author, MAXAUTL);
        printf("������۸�: \n");
        scanf("%f", &library[count++].value);
        while(getchar() != '\n')
            continue;      //����������
        if(count < MAXBKS)
            printf("��������һ���顣 \n");
    }
    if(count > 0)      //����������д��鼮
    {
        printf("����б�:\n");
        for(index = 0; index < count; index++) //�����Ѵ�����鼮
            printf("%s = %s:$%.2f\n", library[index].title, library[index].author, library[index].value);   //�����ݴ�ӡ����
    }
    else{
        printf("û���顣  \n");     //����ʹ�ӡû��
    }
    return 0;
}

char * s_gets(char * st, int n){      //�����ı�(����)����
    char * ret_val;
    char * find;
    ret_val = fgets(st, n, stdin);
    if(ret_val){
        find = strchr(st, '\n');   //���һ��з�
        if(find)      //�����ַ����NULL
            *find = '\0';    //�ڴ˴�����һ�����ַ�
        else
            while(getchar() != '\n')
                continue;
    }
    return ret_val;
}