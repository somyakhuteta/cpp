//binary trees

#include <iostream>
using namespace std;
#include <vector>

// class BinaryTree{
// public:
//     // cout << "a single node can have atMost 2 nodes connected to it and if more than 2 childer then it comes in general trees categories";
//     // cout << "top most element is called root" << endl;
//     // cout << "leaf nodes are those which has no children, the nodes children are known as left child and right child";

//     // cout << "ancestor are called parent and parents parents ";

//     // cout << " descendents are sub child of the parents";
//     int height =  0;
//     for(int i = height; i<=544; i++){
//         height = height + arr[i];
        
//     };
// };

class Node{
public:
    int data;
    Node* left;
    Node* right;
    Node(int data){
        this->data;
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

}
int main(){
    // vector<int> arr = {1, 2, 0 , 3, 4, 5,6, 1, 2, 3, 4, 5, 6, -1,9};
    vector<int> binaryTree = {};
    // vector<int> arr2 = {1, 5, 8, 10, 34, 25, 67, 980, 33, 57, 3, 6, 4, 5, 8, 3 ,6,74, 67, 5,6 , 2,3, 68, 99, 100, 121, 12, 3, 1234, 554, 876};
    // vector<int> arr3 = {3, 4, 5, 64, 5, 6, 7, 8, 9, 0, 65, 45, 34, 2,3 45, 4,5 6, 2, 56 ,5,5,45, 0, 8, 9};
    // vector<int>arr4 = {};
    return 0;
};



//four types of traversals 