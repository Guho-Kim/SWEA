// [SWEA] No 1233. [S/W 문제해결 기본] 9일차 - 사칙연산 유효성 검사
#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<queue>
#include<stack>

using namespace std;

constexpr size_t MAX_NODE = 200*10;

typedef char Data;

struct Node{
    int key;
    Data data;
    Node *left, *right;
};

int node_count;
int stack_count;
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
    stack_count=0;
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

stack<int> s;
int a[2];
bool possible;

void traversal_rec(Node* node){
	if(node == nullptr) return;
	traversal_rec(node->left);
	traversal_rec(node->right);
//    cout << node->data<<" ";
    if(node->data != '+' && node->data != '-' && node->data != '*' && node->data != '/'){
        s.push(int(node->data)-48);
    } else if(s.size() >= 2){
        for(int i=0; i<2; i++){
            a[i]=s.top();
            s.pop();
        }
        
        switch(node->data){
            case '+':
                s.push(a[0]+a[1]);
                break;
            case '-':
                s.push(a[0]-a[1]);
                break;
            case '*':
                s.push(a[0]*a[1]);
                break;
            case '/':
                s.push(a[0]+a[1]);
                break;
            default:
                break;
        }
        
    } else{
        possible = false;
    }




}


int main(){
	for(int test_case = 1; test_case <= 10; test_case++){	
		int N;
		cin >> N;
		cin.ignore();
		init();
        while(!s.empty()) s.pop();
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
			insert(vec[1][0]);
		}

        possible = true;
		traversal_rec(root);
        cout << "#" << test_case << " ";
        if(possible) cout << "1";
        else cout << "0";
		cout << endl;
	
	}

    return 0;
}