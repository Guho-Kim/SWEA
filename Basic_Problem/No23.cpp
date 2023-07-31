/*
#include <iostream>
#include <algorithm>
#define MAX_N 100001

using namespace std;

int heap[MAX_N];
int heapCnt;

void init()
{
    heapCnt = 1;
}

void push(int data)
{
    int ppivot, pivot;

    ppivot = heapCnt;
    heap[heapCnt++] = data;

    if (heapCnt == 2)
        return;

    while (1)
    {
        pivot = ppivot;
        ppivot = ppivot >> 1;

        if (pivot == 1)
            return;
        else if (heap[ppivot] < data)
        {
            heap[pivot] = heap[ppivot];
            heap[ppivot] = data;
        }
        else
            return;
    }
}

void pop()
{
    if (heapCnt == 1)
        return;

    heap[1] = heap[--heapCnt];

    if (heapCnt <= 2)
        return;

    int ppivot, pivot, temp;
    pivot = 1;

    while (1)
    {
        ppivot = pivot;
        pivot = pivot << 1;
        if (pivot >= heapCnt)
            return;
        if(heap[pivot]<heap[pivot+1]){
            pivot++;
        }

        if (heap[ppivot] < heap[pivot])
        {
            temp = heap[ppivot];
            heap[ppivot] = heap[pivot];
            heap[pivot] = temp;
        }
        else
            return;
    }
}

int top()
{
    return heap[1];
}

void view()
{
    int j=2;
    for (int i = 1; i < heapCnt; i++)
    {
        if(j==i){
            cout<<endl;
            j=j<<1;
        }
        cout << heap[i] << " ";
    }
    cout << endl;
}

int main()
{

    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        init();
        cout << "#" << test_case;
        int N;
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            int operation, x, c;
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
                    c = top();
                    pop();
                    cout <<" "<< c;
                }
            }
            //view();
        }
        cout << endl;
    }
    return 0;
}

*/

#include <iostream>
using namespace std;

#define MAXN 100000

int heap[MAXN];
int heapCnt;

void Add(int val) {
    int pivot = heapCnt;
    heap[heapCnt++] = val;
    while(pivot > 0) {
        int ppivot = pivot;
        pivot--;
        pivot = pivot >> 1;
        if(heap[pivot] < val) {
            heap[ppivot] = heap[pivot];
            heap[pivot] = val;
        } else return;
    }
    return;
}
int Pop() {
    if(heapCnt == 0) return -1;
    int val = heap[0];
    heapCnt--;
    heap[0] = heap[heapCnt];
    int pivot = 0;
    while(true) {
        int ppivot = pivot;
        pivot = pivot << 1;
        pivot++;
        if(pivot >= heapCnt) {
            break;
        } else if(pivot + 1 == heapCnt) {
            if(heap[ppivot] > heap[pivot]) break;
            int tmp = heap[ppivot];
            heap[ppivot] = heap[pivot];
            heap[pivot] = tmp;
            break;
        } else {
            if(heap[pivot] < heap[pivot + 1]) pivot++;
            if(heap[ppivot] > heap[pivot]) break;
            int tmp = heap[pivot];
            heap[pivot] = heap[ppivot];
            heap[ppivot] = tmp;
        }
    }
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cout << '#' << tc << ' ';
        heapCnt = 0;
        int N;
        cin >> N;
        for(int n = 0; n < N; n++) {
            int act;
            cin >> act;
            if(act == 1) {
                int num;
                cin >> num;
                Add(num);
            } else {
                cout << Pop() << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}