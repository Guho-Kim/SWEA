#include <iostream>
#define MAX_N 100001

using namespace std;

int heap[MAX_N];
int heapCnt;

void push(int data)
{
    int ppivot, pivot;

    ppivot = heapCnt;
    heap[heapCnt++] = data;

    while (ppivot > 1)
    {
        pivot = ppivot;
        ppivot = ppivot >> 1;

        if (heap[ppivot] < data)
        {
            heap[pivot] = heap[ppivot];
            heap[ppivot] = data;
        }
        else
            return;
    }
    return;
}

int pop(){
    if (heapCnt == 1) return -1;
    int result = heap[1];
    heap[1] = heap[--heapCnt];
    int pivot = 1;
    while (1){
        int ppivot = pivot;
        pivot = pivot << 1;
        if(pivot >= heapCnt) break;
        else{
            if (heap[pivot] < heap[pivot + 1])
                pivot++;
            
            if(heap[ppivot] > heap[pivot]) break;
            int temp = heap[ppivot];
            heap[ppivot] = heap[pivot];
            heap[pivot] = temp;
        }
    }
    return result;
}


void view()
{
    int j = 2;
    for (int i = 1; i < heapCnt; i++)
    {
        if (j == i)
        {
            cout << endl;
            j = j << 1;
        }
        cout << heap[i] << " ";
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        heapCnt = 1;
        cout << "#" << test_case;
        int N;
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            int operation, x;
            cin >> operation;
            if (operation == 1)
            {
                cin >> x;
                push(x);
            }
            else if (operation == 2)
            {
                if (heapCnt == 1)
                {
                    cout << " -1";
                }
                else
                {
                    //pop();
                    cout << " " << pop();
                }
            }
            //view();
        }
        cout << endl;
    }
    return 0;
}
