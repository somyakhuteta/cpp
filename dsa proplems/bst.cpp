#include <queue>
#include <iostream>
using namespace std;
#include <vector>

class Node{
public:
    int data;
    Node* left;
    Node* right;
    Node(int data){
        this->data = data;
        left = right = NULL;
    }
};



bool bstsearch(Node* root, int key){
    if(root == NULL){
        return false;
    }
    if(root->data == key){
        return true;
    }
    if(root->data < key){
        return bstsearch(root->left, key);
    }else (root->data < key){
        return bstsearch(root->right, key);
    }
};

Node* insert(Node* root, int val){
    if(root == NULL){
        root = new Node(val);
        return root;
    }

    if(val< root->data){
        root->left = insert(root->left, val);
    }else {
        root->right = insert(root->right, val);
    }
    return root;

}

Node* buildBst(int arr[], int n){
    Node* root = NULL;
    for(int i=0; i<n; i++){
        root = insert(root, arr[i]);
    }
    return root;
}

Node* iS(Node* root){
    while(root->left == NULL){
        root = root->left;
    }
    return root;
}

Node* delNode(Node* root, int val){
    if(root == NULL){
        return NULL;
    }
    if(root->data == val){
        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        }else if(root->left == NULL || root->right || NULL){
            root->left == NULL ? return root->right : return root->left;
        } else {
            root = iS(root->right);

        }

    }else if(val<root->data){
        root->left = delNode(root->left, val);
    }else if (val>root-> data){
        root->right = delNode(root->right, val);
    }
}


int main(){ 
    int arr[] = {5, 1, 4, 5, 3, 6, 2, 7, 9, 8};


    // preOrder(root);
    // postOrder(root);
    // inOrder(root);
    return 0;

};
