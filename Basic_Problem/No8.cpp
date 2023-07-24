#include<iostream>

using namespace std;

struct Node{
    int key;
    char value;
    Node *left, *right;
};

constexpr size_t MAX_NODE = 100*10;
int node_count;
Node node_pool[MAX_NODE];


Node* new_node(int x, char y){
    node_pool[node_count].key = x;
    node_pool[node_count].value = y;
    node_pool[node_count].left = nullptr;
    node_pool[node_count].right = nullptr;
    return &node_pool[node_count++];
}
Node* root;

void init(){
    root = nullptr;
    node_count=0;
}

Node* insert(int x, char y){
    root = insert_rec(root, x, y);
    return root;
}

Node* insert_rec(Node* node, int x, char y){
    if(node == nullptr){
        return new_node(x, y);
    }
    if(x < node->key){
        node->left = insert_rec(node->left, x, y);
    }else if(x > node->key){
        node->right = insert_rec(node->right, x, y);
    }

    return node;
}
void remove(int x) {
	root = remove_rec(root, x);
}
Node* remove_rec(Node* node, int x) {
	if (node == nullptr) {
		return node;
	}

	if (x < node->key) {
		node->left = remove_rec(node->left, x);
	} else if (x > node->key) {
		node->right = remove_rec(node->right, x);
	} else {
		if (node->left == nullptr) {
			return node->right;
		} else if (node->right == nullptr) {
			return node->left;
		}
		const int temp = find_min_key(node->right);
		node->key = temp;
		node->right = remove_rec(node->right, temp);
	}

	return node;
}

int find_min_key(Node* node){
	while (node->left != nullptr) {
		node = node->left;
	}
	return node->key;
}

// O(트리의 높이)
bool find(int x) {
	Node* node = root;
	while (node != nullptr) {
		if (node->key == x) {
			return true;
		}
		node = x < node->key ? node->left : node->right;
	}
	return false;
}

int main(){
    init();



    return 0;
}