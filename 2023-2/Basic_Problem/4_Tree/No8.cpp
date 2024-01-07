// [SWEA] No 1231. [S/W 문제해결 기본] 9일차 - 중위순회

#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<queue>

using namespace std;

constexpr size_t MAX_NODE = 100*10;

typedef string Data;

struct Node{
    int key;
    Data data;
    Node *left, *right;
};

int node_count;
Node node_pool[MAX_NODE];

void init();
void insert(Data data);

Node* new_node(Data data){
    node_pool[node_count].data = data;
    node_pool[node_count].left = nullptr;
    node_pool[node_count].right = nullptr;
    return &node_pool[node_count++];
}
Node* root;

void init(){
    root = nullptr;
    node_count=0;
}

void insert(Data data){
	if(root == nullptr){
		root = new_node(data);
		return;
	}

	queue<Node*> q;
	q.push(root);

	while(!q.empty()){
		Node* front = q.front();
		q.pop();

		if(front->left==nullptr){
			front->left = new_node(data);
			return;
		} else if(front->right == nullptr){
			front->right = new_node(data);
			return;
		} else{
			q.push(front->left);
			q.push(front->right);
		}

	}

}


void traversal_rec(Node* node){
	if(node == nullptr) return;
	traversal_rec(node->left);
	cout << node->data;
	traversal_rec(node->right);


}


int main(){
	for(int test_case = 1; test_case <= 10; test_case++){	
		int N;
		cin >> N;
		cin.ignore();
		init();
		for(int i=0; i<N; i++){
			string str;
			getline(cin, str);
			istringstream ss(str);
			string stringBuffer;
			vector<string> vec;
			vec.clear();

			while(getline(ss, stringBuffer, ' ')){
				vec.push_back(stringBuffer);
			}
			insert(vec[1]);
		}
		cout << "#" << test_case << " ";
		traversal_rec(root);
		cout << endl;
	
	}

    return 0;
}