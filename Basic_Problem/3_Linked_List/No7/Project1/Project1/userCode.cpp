#define MAX_NODE 10000

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].prev = nullptr;
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
        head->prev = newNode;
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
        newNode->prev = current;
    }

}

void addNode2Num(int data, int num) {
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
        for (int i = 0; i < num - 2; i++) {
            current = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = newNode;
            newNode->next = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }

}

int findNode(int data)
{
    Node* current;
    current = head;
    int cnt = 0;
    while (current!= nullptr) {
        cnt++;
        if (current->data == data) return cnt;
        else {
            current = current->next;
        }
    }

    return 0;

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
            if (current->next->next != nullptr) {
                current->next->next->prev = current;
                current->next = current->next->next;
            }
            else {
                current->next = nullptr;
            }
            

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

int getReversedList(int output[MAX_NODE])
{
    Node* current;
    current = head;
    int cnt = 0;
    if (head == nullptr) {
        return 0;
    }
    
    while (current->next != nullptr) {
        current=current->next;
    }

    while (current->prev != nullptr) {
        output[cnt++] = current->data;
        current = current->prev;
    }
    output[cnt++] = current->data;
    return cnt;
    
}