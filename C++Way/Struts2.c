#include <stdio.h>
#include <string.h>

struct Books
{
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
};

int main(){
    struct Books Book1;     /*���� Book1, ����ΪBooks */
    struct Books Book2;     /*���� Book2, ����ΪBooks */

    /* Book1���� */
    strcpy (Book1.title, "C Programming");
    strcpy (Book1.author, "Nuha Ali");
    strcpy(Book1.subject, "C Programming Tutorial");
    Book1.book_id = 6495407;

    /* Book2x���� */
    strcpy (Book2.title, "Telecom Billing");
    strcpy (Book2.author, "Zara Ali");
    strcpy(Book2.subject, "Telecom Billing Tutorial");
    Book2.book_id = 6495700;

    /*���Book1��Ϣ */
    printf("Book1 title : %s\n", Book1.title);
    printf("Book1 author : %s\n", Book1.author);
    printf("Book1 subject : %s\n", Book1.subject);
    printf("Book1 book_id : %s\n", Book1.book_id);

    /*���Book2��Ϣ */
    printf("Book2 title : %s\n", Book2.title);
    printf("Book2 author : %s\n", Book2.author);
    printf("Book2 subject : %s\n", Book2.subject);
    printf("Book2 book_id : %s\n", Book2.book_id);

    return 0;
}