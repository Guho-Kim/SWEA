

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_DIR 50000
#define MAX_CHILD 500

//. 제출시 삭제
#include<iostream>
using namespace std;


// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.

int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}

int mstrlen_slash(const char* a)
{
	bool slash = false;
	int len = 0;

	while (!slash) {
		if (a[len] == '/') slash=true;
		len++;
	}
	return len;
}

int mstrlen_last_slash(const char* a)
{
	int slash = 0;
	int len = 0;
	while (a[len+1] != '\0') {
		if (a[len] == '/') slash = len;
		len++;
	}
	return slash;
}

struct Node {
	char name[NAME_MAXLEN+1];
	int childCount;
	int num_child;
	Node* child[MAX_CHILD];
};

Node* root;
Node node_pool[MAX_DIR];
int nodeCount;

Node* new_node(char name[NAME_MAXLEN + 1]) {
	mstrcpy(node_pool[nodeCount].name, name);
	node_pool[nodeCount].childCount = 0;
	node_pool[nodeCount].num_child = 0;
	for (int i = 0; i < MAX_CHILD; i++) node_pool[nodeCount].child[i] = nullptr;
	return &node_pool[nodeCount++];
}

void init(int n) {
	char name[NAME_MAXLEN + 1] = "/";
	nodeCount = 0;
	root = new_node(name);
}


Node* find_node(Node* node, char path[PATH_MAXLEN + 1]) {
	char dir[NAME_MAXLEN + 1];
	int current_len;

	// root에 만들 경우 바로 만들고 종료
	if (mstrlen(path) == 1) {
		return node;
	}

	current_len = mstrlen_slash(&path[1]);		
	mstrncpy(dir, &path[1], current_len - 1);

	for (int i = 0; i < node->childCount; i++) {
		if (node->child[i] != nullptr) {
			if (!mstrcmp(node->child[i]->name, dir)) {
				return find_node(node->child[i], &path[current_len]);
			}
		}
	}
	return node;
}

void viewTree(Node* node) {
	cout << node->name << " ";
	for (int i = 0; i < node->childCount; i++) {
		if (node->child[i] != nullptr) {
			viewTree(node->child[i]);
		}
	}
}


void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* node = find_node(root, path);
	node->child[(node->childCount)++] = new_node(name);
	node->num_child++;

	
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	char parentPath[PATH_MAXLEN + 1];
	mstrncpy(parentPath, path, mstrlen_last_slash(path) + 1);
	Node* parent = find_node(root, parentPath);
	Node* node = find_node(root, path);
	for (int i = 0; i < parent->childCount; i++) {
		if (parent->child[i] != nullptr) {
			if (!mstrcmp(parent->child[i]->name, node->name)) {
				parent->child[i] = nullptr;
				parent->num_child--;
				return;
			}
		}
	}
	
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* src = find_node(root, srcPath);
	Node* dest = find_node(root, dstPath);

	if (src == nullptr || dest == nullptr) {
		return;
	}
	cmd_mkdir(dstPath, src->name);
	
	char newSrcPath[PATH_MAXLEN + 1];
	char newDstPath[PATH_MAXLEN + 1];
	if (src->num_child == 0) return;

	mstrcpy(newDstPath, dstPath);

	int src_len;
	int dst_len = mstrlen(dstPath);

	for (int i = 0; i < mstrlen(src->name); i++) {
		newDstPath[dst_len++] = src->name[i];
	}
	newDstPath[dst_len++] = '/';
	newDstPath[dst_len++] = '\0';



	for (int i = 0; i < src->num_child; i++) {
		if (src->child[i] != nullptr) {


			mstrcpy(newSrcPath, srcPath);
			src_len = mstrlen(srcPath);
			for (int j = 0; j < mstrlen(src->child[i]->name); j++) {
				newSrcPath[src_len++] = src->child[i]->name[j];
			}
			newSrcPath[src_len++] = '/';
			newSrcPath[src_len++] = '\0';
			cmd_cp(newSrcPath, newDstPath);
		}
	}

	
	
}


void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	char parentPath[PATH_MAXLEN + 1];
	mstrncpy(parentPath, srcPath, mstrlen_last_slash(srcPath) + 1);

	Node* parent = find_node(root, parentPath);
	Node* src = find_node(root, srcPath);
	Node* dest = find_node(root, dstPath);

	dest->child[dest->childCount++] = src;
	for (int i = 0; i < parent->childCount; i++) {
		if (parent->child[i] != nullptr) {
			if (!mstrcmp(parent->child[i]->name, src->name)) {
				parent->child[i] = nullptr;
				break;
			}
		}
	}
	parent->num_child--;
	dest->num_child++;

	
	
}

int countNode(Node* node) {
	if (node == nullptr) return 0;
	else {
		int count = 1;
		for (int i = 0; i <= node->childCount; i++) {
			count+= countNode(node->child[i]);
		}
		return count;
	}
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	Node* node = find_node(root, path);
	cout << countNode(node)-1 << " " << endl;
	return countNode(node)-1;
}

