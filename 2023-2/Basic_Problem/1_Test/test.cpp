#include<iostream>
#include<vector>

using namespace std;

void view(size_t *ptr){
    for(int i=0; i<3; i++){
        cout<<ptr[i]<<" ";
    }

}
int main(){
    int k=0;
    size_t arr[10][5];
    for(int i=0; i<10; i++){
        for(int j=0; j<5; j++){
            arr[i][j]=++k;
        }
    }
    view(&arr[2][2]);
    return 0;
}