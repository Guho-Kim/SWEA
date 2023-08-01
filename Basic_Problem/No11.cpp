// [SWEA] No 1248. [S/W 문제해결 응용] 3일차 - 공통조상
#include<iostream>
#include<unordered_set>
#include<cmath>
using namespace std;

constexpr size_t MAX_NODE = 100001;

struct Node{
    int data;
    Node *parent;
    Node *left, *right;
};

Node Nodes[MAX_NODE];

int find_cor_parent(int N1, int N2){
    unordered_set<int> set;
    while(Nodes[N1].parent != nullptr){
        N1 = Nodes[N1].parent->data;
        set.insert(N1);
    }
    while(Nodes[N2].parent != nullptr){
        N2 = Nodes[N2].parent->data;
        if(set.count(N2)){
            return N2;
        }
    }
}
int sub_tree_size;

void find_tree_size(int node){
    if(Nodes[node].left != nullptr){
        find_tree_size(Nodes[node].left->data);
    }
    if(Nodes[node].right != nullptr){
        find_tree_size(Nodes[node].right->data);
    }
    sub_tree_size++;
}


int main(){
    int T;
    cin >> T;
	for(int test_case = 1; test_case <= T; test_case++){	
        int cor_parent, tree_size;
        int p, c;
        int V, E, N1, N2;
        cin >> V >> E >> N1 >> N2;
        for(int i=1; i<=V; i++){
            Nodes[i].data=i;
            Nodes[i].parent=nullptr;
            Nodes[i].left=nullptr;
            Nodes[i].right=nullptr;
        }

        for(int i=0; i<E; i++){
            cin >> p >> c;
            Nodes[c].parent = &Nodes[p];
            if(Nodes[p].left == nullptr){
                Nodes[p].left = &Nodes[c];
            } else{
                Nodes[p].right = &Nodes[c];
            }
        }

        cor_parent = find_cor_parent(N1, N2);

        sub_tree_size=0;
        find_tree_size(cor_parent);
        tree_size=sub_tree_size;
        cout<<"#"<<test_case<<" "<<cor_parent<<" "<<tree_size<<endl;
    }
    return 0;
}