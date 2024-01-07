// [SWEA] No 1230. [S/W 문제해결 기본] 8일차 - 암호문3

#include<iostream>
#include<iterator>
#include<list>

using namespace std;

int main(){
    int test_case;
    int T;
    int N;
    char I;
    int x, y, s;
    int M;

    for(test_case=1; test_case<=10; test_case++){
        list<int> myList;
        list<int>::iterator iter;

        cin>>N;    
        for (int i=0; i<N; i++){
            cin>>M;
            myList.push_back(M);
        }

        cin>>M;
        for(int i=0; i<M; i++){
            cin >> I;
            switch(I){
                case 'I':
                    cin >> x >> y;
                    iter=myList.begin();
                    advance(iter, x);
                    for(int i=0; i<y; i++){
                        cin >> s;
                        myList.insert(iter, s);
                    }

                    break;
                case 'D':
                    cin >> x >> y;
                    iter=myList.begin();
                    advance(iter, x);
                    for(int i=0; i<y; i++){
                        iter = myList.erase(iter);
                    }


                    break;
                case 'A':
                    cin >> y;
                    for(int i=0; i<y; i++){
                        cin >> s;
                        myList.push_back(s);
                    }
                    break;
            }


        }
        cout<<'#'<<test_case<<' ';
        iter=myList.begin();
        for(int i=0; i<10; i++){
            cout<<*iter<<' ';
            iter++;
        }
        cout<<endl;

    }
    return 0;
}
