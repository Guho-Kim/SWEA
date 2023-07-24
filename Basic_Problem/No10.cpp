#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<queue>
#include<stack>

using namespace std;

constexpr size_t MAX_NODE = 1000*10;

typedef string Data;

struct Node{
    int key;
    int left_key;
    int right_key;
    Data data;
    Node *left, *right;
};

int node_count;
int stack_count;
Node node_pool[MAX_NODE];

void init();

Node* new_node(Data data, int k, int lk, int rk){
    node_pool[node_count].key = k;
    node_pool[node_count].left_key = lk;
    node_pool[node_count].right_key = rk;
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

void insert(vector<string> vec, int num_child){
	int k = stoi(vec[0]);
    Data data = vec[1];
    int lk=0;
    int rk=0;
    if(num_child==1){
        lk = stoi(vec[2]);
    } else if(num_child==2) {
        lk = stoi(vec[2]);
        rk = stoi(vec[3]);
    }


    if(root == nullptr){
		root = new_node(data, k, lk, rk);
		return;
	}

	queue<Node*> q;
	q.push(root);

	while(!q.empty()){
		Node* front = q.front();
		q.pop();

		if(front->left==nullptr){
            if(front->left_key == k){
                front->left = new_node(data, k, lk, rk);
                return;
            }
		} else if(front->right == nullptr){
            if(front->right_key == k){
                front->right = new_node(data, k, lk, rk);
                return;
            }
		} else{
			q.push(front->left);
			q.push(front->right);
		}

	}

}

stack<int> s;
int a[2];
int result=0;

void traversal_rec(Node* node){
	if(node == nullptr) return;
	traversal_rec(node->left);
	traversal_rec(node->right);
    if(node->data[0] != '+' && node->data[0] != '-' && node->data[0] != '*' && node->data[0] != '/'){
        s.push(stoi(node->data));
    } else if(s.size() >= 2){
        for(int i=0; i<2; i++){
            a[i]=s.top();
            s.pop();
        }
        
        switch(node->data[0]){
            case '+':
                s.push(a[1]+a[0]);
                break;
            case '-':
                s.push(a[1]-a[0]);
                break;
            case '*':
                s.push(a[1]*a[0]);
                break;
            case '/':
                s.push(a[1]/a[0]);
                break;
            default:
                break;
        }
        result = s.top();

    } 



}


int main(){
	for(int test_case = 1; test_case <= 10; test_case++){	
		int N;
        int index;
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
			insert(vec, vec.size()-2);
		}

		traversal_rec(root);
        cout << "#" << test_case << " ";
        cout << result;
		cout << endl;
	
	}

    return 0;
}