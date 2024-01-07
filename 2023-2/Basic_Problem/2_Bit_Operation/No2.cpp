// [SWEA] No10726. 이진수 표현

#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
    int N, M;
    bool C;
    cin>>T;

    for(test_case=1; test_case<=T; ++test_case){
        cin >> N >> M;
        C = true;
        for(int i=N-1; i>=0; --i){
            if(!(M & (1 << i))){
                C = false;
                break;
            }

        }
        if(C)
            cout<< "#" << test_case << " ON" << endl;
        else
            cout<< "#" << test_case << " OFF" << endl;
    }
    return 0;
}
