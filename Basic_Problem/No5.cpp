#include<iostream>
#include<iterator>
#include<list>

using namespace std;

void viewList(list<int>myList){
    for(auto it = myList.begin(); it != myList.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
}


int main(){
    int test_case;
    int T;
    int N, M, L;
    char I;
    int val, x, y;
    cin >> T;

    for(test_case=1; test_case<=T; test_case++){
        list<int> myList;
        list<int>::iterator iter;

        cin >> N >> M >> L;

        for (int i=0; i<N; i++){
            cin>>val;
            myList.push_back(val);
        }

        for(int i=0; i<M; i++){
            cin >> I;
            switch(I){
                case 'I':
                    cin >> x >> y;
                    iter=next(myList.begin(), x);
                    myList.insert(iter, y);
                    break;

                case 'D':
                    cin >> x;
                    iter=next(myList.begin(),x);
                    myList.erase(iter);
                    break;

                case 'C':
                    cin >> x >> y;
                    iter=next(myList.begin(), x);
                    *iter=y;
                    break;
            }

        }
        cout<<'#'<<test_case<<' ';
        iter=next(myList.begin(),L);

        if(myList.size()>L){
            cout<<*iter<<endl;
        }
        else{
            cout<<"-1"<<endl;
        }

    }
    return 0;
}
