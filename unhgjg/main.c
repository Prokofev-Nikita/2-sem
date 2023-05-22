#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_OF_BUFFER 128
#define SIZE_OF_ANSWER 3

typedef struct Node {
    char *data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(char* value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(value);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* loadTreeFromFile(FILE* fp){
    int index = 0;
    char buffer[SIZE_OF_BUFFER];
    fscanf(fp, "%d: %[^\n]", &index, buffer);
    if (strcmp(buffer,"null") == 0){
        return NULL;
    }
    Node* node = createNode(buffer);
    node->left = loadTreeFromFile(fp);
    node->right = loadTreeFromFile(fp);
    return node;
}

void saveTree(Node* node,FILE* fp,int n){
    if (node == NULL) {
        fprintf(fp, "%d: null\n", n);
        return;
    }
    fprintf(fp, "%d: %s\n", n, node->data);
    saveTree(node->left, fp, n * 2);
    saveTree(node->right, fp, n * 2 + 1);
}

void freeTree(Node *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node->data);
    free(node);
}

void game(Node* root,FILE* fp) {
    char* answer = (char*)malloc(3);
    while (1) {
        Node *present = root;
        Node *parent = NULL;
        int left = 0;

        while (present->left != NULL || present->right != NULL) {
            printf("%s\n Введите да или нет:", present->data);
            scanf("%s",&answer);
            parent = present;
            if (strcmp("да",answer) == 0 || strcmp("Да",answer) == 0 || strcmp("ДA",answer) == 0) {
                present = present->left;
                left = 1;
            } else {
                present = present->right;
                left = 0;
            }
        }

        printf("Это %s?\n Введите да ли нет:", present->data);
        scanf("%s",&answer);
        if (strcmp("нет",answer) == 0 || strcmp("Нет",answer) == 0) {
            printf("Тогда что это?\n");
            scanf("%*c%[^\n]", &answer);
            Node *newAnswer = createNode(answer);
            printf("Какой вопрос можно задать,чтобы понять что это есть  именно это?)\n");
            scanf("%*c%[^\n]", &answer);
            Node *newQuestion = createNode(answer);

            printf("На этот вопрос нужно ответить да?(да/нет)");
            scanf("%s", &answer);

            if (strcmp("нет",answer) == 0 || strcmp("Нет",answer) == 0) {
                newQuestion->left = present;
                newQuestion->right = newAnswer;
            } else {
                newQuestion->left = newAnswer;
                newQuestion->right = present;
            }
            if (parent == NULL) {
                root = newQuestion;
            } else if (left) {
                parent->left = newQuestion;
            } else {
                parent->right = newQuestion;
            }
        }

        printf("Сыграем ещё разок? :)");
        scanf("%s", &answer);
        if (strcmp("нет",answer) == 0 || strcmp("Нет",answer) == 0) {
            break;
        }
        saveTree(root ,fp, 1);
    }

}

int main()
{
    FILE* file = fopen("question.txt","r+");
    Node* root = loadTreeFromFile(file);
    game(root,file);
    fclose(file);
    return 0;
}