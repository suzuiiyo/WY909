#include<iostream>
using namespace std;

int main(){
    enum rank{
        first, second, third
    };

    int nRank=1;
    switch(nRank){
        case first:
            cout << "��һ��";
            break;
        
        case second:
            cout << "�ڶ���";
            break;
        
        case third:
            cout << "������";
            break;
        
        default:
            break;
    }
    //system("pause");
    return 0;
}