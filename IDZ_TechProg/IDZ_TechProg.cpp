#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#define max(a, b) ((a > b) ? a : b)
#define ARRAY_SIZE 3
#define STRING_LENGHT 21

using namespace std;

struct Tree_AVL {
    int key;
    /*int arr[ARRAY_SIZE];
    const char str[STRING_LENGHT];*/
    struct Tree_AVL* pLeft;
    struct Tree_AVL* pRight;
    int height;
};

int getHeight(struct Tree_AVL* root) {
    return (root == NULL) ? 0 : root->height;
}

struct Tree_AVL* newNode(const int key) {
    struct Tree_AVL* newNode = (struct Tree_AVL*)malloc(sizeof(struct Tree_AVL));
    newNode->key = key;
    /*for (int i = 0; i < ARRAY_SIZE; i++) {

    }
    sprintf(newNode->str, "person %d", );*/
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    newNode->height = 1;
    return newNode;
}

struct Tree_AVL* rightRotate(struct Tree_AVL* y) {
    struct Tree_AVL* x = y->pLeft;
    struct Tree_AVL* T2 = x->pRight;

    x->pRight = y;
    y->pLeft = T2;

    y->height = max(getHeight(y->pLeft), getHeight(y->pRight)) + 1;
    x->height = max(getHeight(x->pLeft), getHeight(x->pRight)) + 1;

    return x;
}

struct Tree_AVL* leftRotate(struct Tree_AVL* x) {
    struct Tree_AVL* y = x->pRight;
    struct Tree_AVL* T2 = y->pLeft;

    y->pLeft = x;
    x->pRight = T2;

    x->height = max(getHeight(x->pLeft), getHeight(x->pRight)) + 1;
    y->height = max(getHeight(y->pLeft), getHeight(y->pRight)) + 1;

    return y;
}

int getBalance(struct Tree_AVL* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->pLeft) - getHeight(node->pRight);
}

struct Tree_AVL* balancingTree(Tree_AVL* root) {

    int balance = getBalance(root);
    // Небалансировка LL
    if (balance > 1 && getBalance(root->pLeft) >= 0)
        return rightRotate(root);

    // Небалансировка LR
    if (balance > 1 && getBalance(root->pLeft) < 0) {
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }

    // Небалансировка RR
    if (balance < -1 && getBalance(root->pRight) <= 0)
        return leftRotate(root);

    // Небалансировка RL
    if (balance < -1 && getBalance(root->pRight) > 0) {
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }
    return root;
}

struct Tree_AVL* insertNode(struct Tree_AVL* root, int key) {
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->pLeft = insertNode(root->pLeft, key);
    else if (key > root->key)
        root->pRight = insertNode(root->pRight, key);
    else
        return root;

    root->height = max(getHeight(root->pLeft), getHeight(root->pRight)) + 1;
    root = balancingTree(root);
    return root;
}

//void ndcpy(Tree_AVL* final, Tree_AVL* source) {
//    final->height = source->height;
//    final->key = source->key;
//    strcpy(final->str, source->str);
//    final->arr[0] = soucre->arr[0];
//    final->arr[1] = soucre->arr[1];
//    final->arr[2] = soucre->arr[2];
//
//}

struct Tree_AVL* minValueNode(struct Tree_AVL* root)
{
    Tree_AVL* pCur = root;
    while (pCur->pLeft)
        pCur = pCur->pLeft;
    return pCur;
}

struct Tree_AVL* deleteNode(struct Tree_AVL* root, const int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->pLeft = deleteNode(root->pLeft, key);
    else if (key > root->key)
        root->pRight = deleteNode(root->pRight, key);

    else {
        // Узел с одним или без дочерних элементов
        if ((root->pLeft == NULL) || (root->pRight == NULL)) {
            struct Tree_AVL* tmp = (root->pLeft) ? root->pLeft : root->pRight;

            // Узел без дочерних элементов
            if (tmp == NULL) {
                tmp = root;
                root = NULL;
            }
            else // Узел с одним дочерним элементом
                *root = *tmp;

            free(tmp);
        }
        else {
            // Узел с двумя дочерними элементами
            struct Tree_AVL* tmp = minValueNode(root->pRight);

            root->key = tmp->key;

            root->pRight = deleteNode(root->pRight, tmp->key);
        }
    }
    root->height = max(getHeight(root->pLeft), getHeight(root->pRight)) + 1;
    root = balancingTree(root);
    return root;
}

int searchNode(Tree_AVL* root, const int key) {
    if (root == NULL) {
        printf("Node not found\n");
        return -1;
    }
    if (root->key == key) {
        printf("Value of searching node: %d\n", root->key);
        return 1;
    }
    if (key < root->key)
        searchNode(root->pLeft, key);
    else if (key > root->key)
        searchNode(root->pRight, key);
}
Tree_AVL* changeNode(Tree_AVL* root,  const int key) {
    if (searchNode(root, key) == -1) return root;
    root = deleteNode(root, key);
    int newkey;
    printf("Enter new value: ");
    scanf("%d", &newkey);
    root = insertNode(root, newkey);
    return root;
}


void preOrder(struct Tree_AVL* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->pLeft);
        preOrder(root->pRight);
    }
}

void postOrder(Tree_AVL* root) {
    if (root) {
        postOrder(root->pLeft);
        postOrder(root->pRight);
        printf("%d ", root->key);
    }
}

void inOrder(Tree_AVL* root) {
    if (root) {
        inOrder(root->pLeft);
        printf("%d ", root->key);
        inOrder(root->pRight);
    }
}

//void printTree(Tree_AVL* root, const int lvl) {
//    if (root == NULL) return;
//    if (root != NULL) {
//        if (lvl == 0)
//        {
//            printf("root->", root->key);
//            
//        }
//        for (int i = 0; i < lvl; i++) {
//            printf("   ");
//        }
//        printf("lvl%d->%d\n", lvl, root->key);
//        printTree(root->pLeft, lvl + 1);
//        printTree(root->pRight, lvl + 1);
//    }
//    return;
//
//}

void printTree(Tree_AVL* root, string prefix) {
    if (root == NULL) return;

    cout << prefix << "{ key: " << root->key << endl;

    prefix += "     ";

    printTree(root->pLeft, prefix + "left: ");
    printTree(root->pRight, prefix + "right:");

    cout << prefix << "}" << endl;
    return;

}

void deleteTree(Tree_AVL*& root) {
    if (root) {
        deleteTree(root->pLeft);
        deleteTree(root->pRight);
        free(root);
        //root = NULL;
    }
}
void generateTree(Tree_AVL*& root, const int size) {
    for (int i = 0; i < size; i++) {
        int key = rand() % 150 + 1;
        root = insertNode(root, key);
    }
    
}
int countLines(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return -1;
    }
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    fclose(file);
    return count;
}


Tree_AVL* menu1(Tree_AVL* root) {
menu:
    printf("1. Generate AVL tree (random).\n2. Insert from file.\n3. End of Programm.\n");
    
    char selection;
    fflush(stdin);
    scanf("%c", &selection);
    if (selection == '1') {
        printf("Enter size of tree (count of nodes): ");
        int size;
        scanf("%d", &size);
        //fflush(stdin);
        generateTree(root, size);

        return root;
    } if (selection == '2') {
        const char filename[] = "Tree_AVL.txt";
        int countL = countLines(filename);
        if (countLines(filename) == -1) {
            printf("Error for rerading a file - its not exist.\n");
            return NULL;
        }
        int* Tree_Array = (int*)malloc(countL * sizeof(int));
        FILE* file = fopen(filename, "r");
        for (int i = 0; i < countL; i++) {
            fscanf(file, "%d", &Tree_Array[i]);
            root = insertNode(root, Tree_Array[i]);
        }
        fclose(file);
        return root;
    } if (selection == '3') {
        return NULL;
    }
    else {
        printf("ERROR\n");
        goto menu;
    }
}

void menu2(Tree_AVL*& root) {
menu:
    printf("\n\n1. Insert value in tree.\n2. Delete value into tree.\n3. Change value by key in tree.\n"
        "4. Search in tree.\n5. Print Tree (pre-order, post-order, in-order).\n6. Delete tree.\n7. Exit.\n\n");
    
    char selection;
    fflush(stdin);
    scanf("%c", &selection);
    int any_key;
    switch (selection) {
    case '1':
        //insert
        printf("Enter the key witch will be inserted\n"); 
        scanf("%d", &any_key);
        //fflush(stdin);
        root = insertNode(root, any_key);
        break;
    case '2':
        //delete
        printf("Enter the key witch will be deleted:\n");
        //fflush(stdin);
        scanf("%d", &any_key);
        root = deleteNode(root, any_key);
        break;
    case '3':
        //change
        printf("Enter the key witch will be changed:\n");
        //fflush(stdin);
        scanf("%d", &any_key);
        root = changeNode(root, any_key);
        break;
    case '4':
        //search
        printf("Enter the key witch will be searched:\n");
        //fflush(stdin);
        scanf("%d", &any_key);
        searchNode(root, any_key);
        break;
    case '5':
        //print
        if (root == NULL) {
            printf("Tree is empty\n\n");
            break;
        }
        printf("PreOrder: ");
        preOrder(root);
        printf("\n\nPostOrder: ");
        postOrder(root);
        printf("\n\nInOrder: ");
        inOrder(root);
        printf("\n\n");
        printTree(root, "");
        break;
    case '6':
        //delete tree
        deleteTree(root);
        root = NULL;
        printf("Tree has been deleted.\n");
        break;
    case '7':
        //exit
        deleteTree(root);
        root = NULL;
        printf("Tree has been deleted.\n");
        return;
    default:
        printf("ERROR\n");
        break;
    }
    goto menu;

}

int main() {
    srand(time(NULL));
    struct Tree_AVL* root = NULL;
    root = menu1(root);
    if (root) menu2(root);
    return 0;
}