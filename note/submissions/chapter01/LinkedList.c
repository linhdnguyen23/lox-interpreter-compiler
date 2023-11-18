#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNode {
    struct sNode *next, *prev;
    char *data;
} Node;

Node* createEmptyNode() {
    Node *sNode;
    sNode = malloc(sizeof(Node));
    sNode->next = NULL;
    sNode->prev = NULL;
    sNode->data = NULL;
    return sNode;
}

Node* createNode(const char* data) {
    Node* sNode = createEmptyNode();
    sNode->data = malloc(sizeof(strlen(data)) + 1);
    strcpy(sNode->data, data);

    return sNode;
}

Node* insert(Node** curr, const char *dataStr) {
    Node* sNode = createNode(dataStr);
    if ((*curr)->prev == NULL) {
        if ((*curr)->data != NULL) {
            (*curr)->next = sNode;
            sNode->prev = *curr;
            *curr = sNode;
        } else {
            *curr = sNode;
        }
    } else {
        (*curr)->next = sNode;
        sNode->prev = *curr;
        *curr = sNode;
    }
    return *curr;
}

Node* find(Node* tail, const char* toFind) {
    if (toFind == NULL) {
        return NULL;
    }
    while(tail != NULL && tail->data != NULL) {
        if (strcmp(tail->data, toFind) == 0) {
            return tail;
        }
        tail = tail->prev;
    }
    return tail;
}

void printNode(Node* sNode) {
    if (sNode != NULL) {
        if (sNode->data != NULL) {
            printf("%s\n", sNode->data);
            return;
        }
    }
    printf("Empty node\n");
}

Node* delete(Node** node, const char* toDelete) {
    Node* found = find(*node, toDelete);
    // front of list
    if (found->prev == NULL) {
        Node* next = found->next;
        found->next = NULL;
        next->prev = NULL;
        found = next;
    } else if (found->next == NULL) { // end of list
        Node* prev = found->prev;
        prev->next = NULL;
        found->prev = NULL;
        found = prev;
    } else {
        found->prev->next = found->next;
        found->next->prev = found->prev;
        found->prev = found->next = NULL;
    }
    return found;
}

void traverse(Node* node) {
    printf("Starting to traverse\n");
    while(node != NULL) {
        printNode(node);
        node = node->prev;
    }
}

int main(int argc, const char* argv[]) {
    Node *llist = createEmptyNode();
    insert(&llist, "one");
    insert(&llist, "two");
    insert(&llist, "three");
    delete(&llist, "three");
    traverse(llist);
    return 0;
}