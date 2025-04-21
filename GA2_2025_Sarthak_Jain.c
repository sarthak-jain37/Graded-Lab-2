//Sarthak Jain 2410110306. This code has been written by me and is not copied from anywhere else.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node{ 
    char data; 
    struct Node *left; 
    struct Node *right;
}Node;

Node* createNode(char data){
    if(data == 'X' || !isalpha(data)){
        printf("Encountered X.\n");
        return NULL;
    }

    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    printf("Node %c added.\n", newnode->data);

    return newnode;
}

Node* search(char data, Node* root){
    if (root == NULL)
        return NULL;

    if (root->data == data)
        return root;

    Node* leftResult = search(data, root->left);
    if (leftResult != NULL)
        return leftResult;

    return search(data, root->right);
}

Node* insert(char tuple[], Node* root){
    Node* newnode = search(tuple[0], root);  // Find the node
    if (newnode == NULL) {
        newnode = createNode(tuple[0]);  // If not found, create the node
    }
    
    Node* left = search(tuple[1], root);
    if (left == NULL) {
        left = createNode(tuple[1]);  // If left child doesn't exist, create it
    }
    
    Node* right = search(tuple[2], root);
    if (right == NULL) {
        right = createNode(tuple[2]);  // If right child doesn't exist, create it
    }

    if (newnode != NULL) {
        newnode->left = left;   // Assign left child
        newnode->right = right; // Assign right child
        printf("\nNewnode : %c\n", newnode->data);
        if(left != NULL)
        printf("Left : %c\n", left->data);
        else
        printf("Left : NULL\n");
        if(right != NULL)
        printf("Right : %c\n\n", right->data);
        else
        printf("Right : NULL\n\n");

    }

    if((newnode != root && (root == left || root == right)) || root == NULL){
         root = newnode;
    }

    printf("Root : %c\n\n", root->data);
    return root;
}

// N L P J F N P X T F X X L X X T X X

Node* parseEmployees(char employees[]){
    int i = 0;
    Node* root = NULL;
    while(employees[i] != '\0'){
        char tuple[3];
        for(int j = 0; j < 3; j++){
            if(employees[i] == '\0') break;
            tuple[j] = employees[i];
            i = i + 2;
        }
        root = insert(tuple, root);
    }
    return root;
}

void inorderTraversal(Node* root){
    if(root == NULL){
        return;
    }

    inorderTraversal(root->left);
    printf("%c ", root->data);
    inorderTraversal(root->right);
}

void parseFile(char* nnn, char* ppp, char employees[], int size){
    FILE* file = fopen("employees.txt","r");

    if(file == NULL){
        printf("Error opening the file");
        return;
    }
    *nnn = fgetc(file); //assign the first letter to nnn
    fgetc(file); //discard the space between the letters
    *ppp = fgetc(file); //assign the second letter to ppp
    fgetc(file); //discard the space between the letters
    
    fgets(employees, size, file); //parse the remaining employees into the string

    fclose(file);
}

int main() {
    char employees[50];
    char nnn, ppp;
    parseFile(&nnn, &ppp, employees, sizeof(employees));
    Node* root = parseEmployees(employees);
    inorderTraversal(root);
    return 0;
}