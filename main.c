#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct Node{ 
    char data; 
    struct Node *left; 
    struct Node *right;
}Node;

Node* createNode(char data){
    if(data == 'X' || !isalpha(data)){
        // printf("Encountered X.\n");
        return NULL;
    }

    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;

    // printf("Node %c added.\n", newnode->data);

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

        // printf("\nNewnode : %c\n", newnode->data);
        // if(left != NULL)
        // printf("Left : %c\n", left->data);
        // else
        // printf("Left : NULL\n");
        // if(right != NULL)
        // printf("Right : %c\n\n", right->data);
        // else
        // printf("Right : NULL\n\n");

    }

    if((newnode != root && (root == left || root == right)) || root == NULL){
         root = newnode;
    }

    // printf("Root : %c\n\n", root->data);
    return root;
}

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

void preorderTraversal(Node* root){
    if(root == NULL){
        return;
    }

    printf("%c ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
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

int printHeight(Node* root){
    if (root == NULL) {
        return 0;
    }

    int leftHeight = printHeight(root->left);
    int rightHeight = printHeight(root->right);

    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

int countBosses(Node* root){
    if(root == NULL) return 0;
    int bosses = 0;

    if(root->left != NULL || root->right != NULL){
        bosses = 1 + countBosses(root->left) + countBosses(root->right);
    }
    else{
        return 0;
    }
    return bosses; 
}

int verifyBST(Node* root, char min, char max){
    if (root == NULL)
        return 1;

    if (root->data <= min || root->data >= max) {
        printf("BST violation at NODE %c\n", root->data);
        return 0;
    }

    return verifyBST(root->left, min, root->data) &&
           verifyBST(root->right, root->data, max);
}

Node* specialFunction(Node* root){
    Node* alpha;
    Node* omicron;
    
    alpha = root;               
    omicron = alpha->right;     
    
    alpha->right = omicron->left;
    omicron->left = alpha;      
    
    return omicron;             
}

void findTeammate(char data, Node* root){
    if (root == NULL)
        return;

    if(root->data == data){
        printf("Confirmed that %c exists in the tree.\n",root->data);
        printf("%c is sole team member.\n", root->data);
        return;
    }

    if (root->left != NULL && root->left->data == data){
        printf("Confirmed that %c is an employee.\n",root->left->data);

        if(root->right != NULL){
            printf("Team mate of %c: %c\n",root->left->data, root->right->data);
        }
        else{
            printf("%c is sole team member.\n", root->left->data);
        }
        return;
    }

    if (root->right != NULL && root->right->data == data){
        printf("Confirmed that %c is an employee.\n",root->right->data);
        
        if(root->left != NULL){
            printf("Team mate of %c: %c\n",root->right->data, root->left->data);
        }
        else{
            printf("%c is sole team member.\n", root->right->data);
        }
        return;
    }

    findTeammate(data, root->left);
    findTeammate(data, root->right);
}


int main() {
    char employees[50];
    char nnn, ppp;
    parseFile(&nnn, &ppp, employees, sizeof(employees));
    Node* root = parseEmployees(employees);

    printf("Inorder : ");
    inorderTraversal(root);

    int height = printHeight(root);
    printf("\n\nThe height of the tree : %d\n", height);

    int bosses = countBosses(root);
    printf("\nThe no. of bosses in the organization : %d\n\n", bosses);

    if(verifyBST(root, 'A' - 1, 'Z' + 1)){
        printf("The Tree is a BST\n");
        printf("CEO : %c\n\n", root->data);
    }
    else{
        printf("The Tree is not a BST\n\n");
    }

    root = specialFunction(root);
    printf("Preorder : ");
    preorderTraversal(root);
    printf("\n\n");

    findTeammate(nnn, root);
    findTeammate(ppp, root);
    

    return 0;
}
