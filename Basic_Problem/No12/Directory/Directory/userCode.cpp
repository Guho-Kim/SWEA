#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_DIR 50000
#define MAX_CHILD 30

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

struct Node {
	char name[NAME_MAXLEN+1];
	int num_child;
	Node* child[MAX_CHILD];
};

Node* root;
Node node_pool[MAX_DIR];
int num_node;

Node* new_node(char name[NAME_MAXLEN + 1]) {
	mstrcpy(node_pool[num_node].name, name);
	for (int i = 0; i < MAX_CHILD; i++) node_pool[num_node].child[i] = nullptr;
	return &node_pool[num_node++];
}

void init(int n) {
	char name[NAME_MAXLEN + 1] = "/";
	num_node = 0;

	root = new_node(name);
	root->num_child = 0;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	if (mstrcmp(path, root->name)) {
		root->child[(root->num_child)++] = new_node(name);
		return;
	}



}

void cmd_rm(char path[PATH_MAXLEN + 1]) {

}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {

}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {

}

int cmd_find(char path[PATH_MAXLEN + 1]) {

	return 0;
}