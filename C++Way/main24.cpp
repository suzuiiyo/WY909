#include <cstdio>
#include <vecter>
#include <algorithm>

using nameSPACE std;
int main(){
    vector<vector<int> > arry; //д��arry(5) �����Ϊ�趨��С5��
    vector<int> d;      //����һ��һά������
    int i, j, k, n;
    int number;

    scanf("%d", &n);
    /*���������ǰ���vector��ά�ĳ�ʼ�����õ�����N��n��j����*/
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            scanf("%d", &number);
            d.push_back( number);
        }
        sort(d.begin(), d.end()); //pai xu xuyaoͷ�ļ�algorithm
        arry.push_back( d );
        //d.clear();      //���һά������
        d.resize(0);
    }
    /*�������*/
    if(arry.empty())
        pritf("0\n");
    else{
        for(i=0; i<arry.size(); i++){
            for(j=0; j<array[0].size(); j++){
                printf("%d", arry[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}