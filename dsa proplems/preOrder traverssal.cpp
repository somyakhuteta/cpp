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

static int idx = -1;

Node* buildTree(vector<int> binaryTree){
    idx++;
    if(binaryTree[idx] == -1){
        return NULL;
    }
    Node* currNode = new Node(binaryTree[idx]);
    currNode->left = buildTree(binaryTree);//left subTree
    currNode->right = buildTree(binaryTree);//right subTree
    
    return currNode;
};
void preOrder(Node* root){
    if(root == NULL){
        return;
    }
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
};
void inOrder(Node* root){
    if(root == NULL){
        return;
    }
    inOrder(root->left);
    cout << root-> data<< " ";
    inOrder(root->right);
};
void postOrder(Node* root){
    if(root == NULL){
        return;
    }
    postOrder(root->left);
    postOrder(root->right); 
    cout << root-> data<< " ";
};

void levelOrderTraversal(Node* root){
    if(root == NULL){
        return;
    }
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* curr = q.front();
        q.pop();
        if(curr == NULL){
            cout << endl;
            if(q.empty()){
                break;
            }
            q.push(NULL);
        } else{
            cout << curr->data << " ";
            if(curr->left != NULL){
                q.push(curr->left);
            }if(curr->right != NULL){
                q.push(curr->right);
            }
            q.push(NULL);
        }
    }

}
int height(Node* root){
    if(root == NULL){
        return 0;
    }
    int leftHt = height(root->left);
    int rightHt = height(root->right);
    return max(leftHt, rightHt) + 1;
}

int noOfNodes(Node* root){
    if(root == NULL){
        return 0;
    }
    return noOfNodes(root->left) + noOfNodes(root->right) + 1; 
}

int sumOfNodes(Node* root){
    if(root == NULL){
        return 0;
    }
    return sumOfNodes(root->right) + sumOfNodes(root->left) + root->data;
};

int main(){ 
    vector<int> binaryTree = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
    Node* root = buildTree(binaryTree);
    // preOrder(root);
    // postOrder(root);
    // inOrder(root);
    cout << "root:" << noOfNodes(root) << endl;
    cout << "sum: " << sumOfNodes(root) << endl;
    return 0;

};
