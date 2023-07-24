#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
    int N;
    int count;
    bool arr[10];
    int num_true;
    int mul_var;
    int N_test;

    cin>>T;
    for(test_case=1; test_case<=T; ++test_case){
        for(int i=0; i<10; i++) arr[i]=false;
        cin>>N;
        count = 0;
        num_true=0;
        mul_var=1;
        while(num_true != 10){
            N_test = N * (mul_var++);
            while(N_test != 0){
                if(!arr[N_test%10]){
                    arr[N_test%10]=true;
                    num_true++;
                }
                N_test/=10;
            }
            count++;

        }

        cout<< "#" << test_case << " " << count*N << endl;
    }
    return 0;
}
