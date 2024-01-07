// [SWEA] No 12303. 기초 Single Linked List 연습

#define MAX_NODE 10000

struct Node {
    int data;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].next = nullptr;
    return &node[nodeCnt++];
}

void init()
{
    head = nullptr;
    nodeCnt = 0;
}

void addNode2Head(int data)
{
    Node* newNode = getNode(data);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        newNode->next = head;
        head = newNode;
    }
}

void addNode2Tail(int data)
{
    Node* newNode = getNode(data);
    Node* current;
    current = head;
    if (head == nullptr) {
        head = newNode;
    }
    else {
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

}

void addNode2Num(int data, int num){
    if (num == 1) {
        addNode2Head(data);
        return;
    }

    Node* newNode = getNode(data);
    Node* current;
    current = head;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        
        for (int i = 0; i < num-2; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

}

void removeNode(int data)
{
    Node* current;
    current = head;
    if (head == nullptr) return;
    else if (head->data == data) {
        head = head->next;
        return;
    }

    while (current->next != nullptr) {
        if ((current->next)->data == data) {
            current->next = (current->next)->next;
            return;
        }
        current = current->next;

    }



}

int getList(int output[MAX_NODE])
{
    Node* current;
    current = head;
    int cnt = 0;
    if (head == nullptr) {
        return 0;
    }
    else {
        while (current->next != nullptr) {
            output[cnt++] = current->data;
            current = current->next;
        }
        output[cnt++] = current->data;
        return cnt;
    }
}