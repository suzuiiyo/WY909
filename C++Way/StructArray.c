#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXTITL 41
#define MAXAUTL 31
#define MAVXBKS 100

char * s_gets(char * st, int n);
struct book{
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};

int main(){
    struct book library[MAVXBKS];       //book���ͽṹ������
    int i;
    int index;
    printf("������Ҫ¼����ٱ�����Ϣ\n");
    do{
        scanf("%d", &index);
    }while(index > MAVXBKS);
    getchar();
    for(i=0; i<index; i++){
        printf("�������%d���������:\n", i+1);
        s_gets(library[i].title, MAXTITL);
        printf("�����������ߵ�����:\n");
        s_gets(library[i].author, MAXAUTL);
        printf("�������鱾�۸�:\n");
        scanf("%f", &library[i].value);
        getchar();
    }
    for(i=0; i<index; i++){
        printf("%d\t%s ��%sд�� ����Ϊ%fԪ\n", i, library[i].title, library[i].author, library[i].value);
    }
    system("pause");
    return 0;
}

char * s_gets(char * st, int n){
    char * ret_val;
    char * find;
    ret_val = fgets(st, n, stdin);
    if(ret_val)
    {
        find = strchr(st, '\n');            //���һ��з�
        if(find)                            //���ҵ�ַ��Ϊ��
            *find = '\0';
        else
            while(getchar() != '\n')
        continue;
    }
    return ret_val;
}